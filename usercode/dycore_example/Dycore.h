#pragma once

#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#include <storage/storage-facility.hpp>
#include "../../wrapper/include/wrappable.h"
#include "dycore_helper.h"

#include <memory>
#include "Dycore.h"
/**
 * This is just an example to attach to state flags to the storage to allow a consistency check between fortran and cpp
 */
template < typename DataStore >
struct dycore_field {
    bool cpp_is_uptodate;
    bool fortran_is_uptodate;
    DataStore field;
};

class Dycore : public wrappable {
  public:
    abstract_storage_info get_abstract_storage_info(const std::string &name, std::vector< int > dims) override {
        return make_abstract_storage_info(storage_info_t(dims[0], dims[1], dims[2]));
    }

    bool is_initialized(const std::string &name) override { return fields_.count(name) > 0; }

    void set_external_pointer(const std::string &name, float *ptr) override {
        // TODO set the external ptr in the existing gridtools field
    }

    void init(const std::string &name, std::vector< int > dims, bool external_ptr, void *ptr) override {
        storage_info_t meta_data(dims[0], dims[1], dims[2]);
        if (external_ptr) {

            fields_.emplace(name,
                dycore_field< data_store_t >{
                    true, true, data_store_t(meta_data, (float_type *)ptr, gridtools::ownership::ExternalCPU, name)});
            std::cout << "initialized a new gridtools field in pointer sharing mode" << std::endl;
        } else {
            fields_.emplace(name, dycore_field< data_store_t >{true, true, data_store_t(meta_data, name)});
            std::cout << "initialized a new gridtools field" << std::endl;
        }
    }

    void *get_pointer(const std::string &name) override {
        if (fields_.count(name) > 0) {
            return (void *)fields_[name].field.get_storage_ptr()->get_cpu_ptr();
        } else
            return nullptr;
    }

    void notify_push(const std::string &name) override { fields_[name].cpp_is_uptodate = true; };
    void notify_pull(const std::string &name) override { fields_[name].fortran_is_uptodate = true; };

    int call(const std::string &action) override {
        if (action == "init") {
            std::cout << "[C++] Init" << std::endl;
            // Prepare configuration
            return WRAPPER_RETURN_SUCCESS;
        }
        if (action == "DoStep") {
            if (!check_cpp_fields_uptodate()) {
                throw std::runtime_error("C++ fields are not up-to date");
            }
            DoStep(input(fields_["some_input"], fields_["some_input"]), output(fields_["some_output"]));
            // Do some stuff to the fortran fields
            return WRAPPER_RETURN_SUCCESS;
        }

        if (action == "check_cpp_fields_uptodate") {
            return check_cpp_fields_uptodate();
        }
        if (action == "check_fortran_fields_uptodate") {
            return check_fortran_fields_uptodate();
        }

        std::cout << "[C++] Got Action " << action << " but don't know how to handle" << std::endl;
        return -1;
        //        throw std::runtime_error("DycoreWrapper.h: Action " + action + " is unknown");
    }

    int call(const std::string &action, void *data) override {
        std::cout << "[C++] action: " << action << ", value = " << *static_cast< int * >(data) << std::endl;
        *static_cast< int * >(data) += 5;
        std::cout << "[C++] add 5 to first value, new value = " << *static_cast< int * >(data) << std::endl;
        return 0;
    }

    bool check_cpp_fields_uptodate() {
        bool uptodate = true;
        for (auto &field : fields_) {
            uptodate = uptodate && field.second.cpp_is_uptodate;
        }

        if (!uptodate)
            std::cout << "a cpp field is not up-to-date." << std::endl;
        else
            std::cout << "all fields are up-to-date. NICE!" << std::endl;

        return uptodate;
    }

    bool check_fortran_fields_uptodate() {
        bool uptodate = true;
        for (auto &field : fields_) {
            uptodate = uptodate && field.second.fortran_is_uptodate;
        }
        return uptodate;
    }

    /**
    * This is an example of the consistency check handling.
    * Some operations shoud be abstracted, e.g. outdate operation.
    */
    template < typename Input, typename Output >
    void DoStep(Input input, Output output) {
        auto & [ u, v ] = input;
        auto & [out] = output;

        // check that all fields are uptodate in cpp
        check_cpp_fields_uptodate();

        // invalidate the output on the fortran side as we are going to change it!
        for_each_in_tuple([](auto &field) { field.fortran_is_uptodate = false; }, output);

        // Do the great timestep
        // do_stuff(input(u),output(out));

        // invalidate all input fields as they are now consumed and should be updated in fortran
        for_each_in_tuple([](auto &field) { field.cpp_is_uptodate = false; }, input);
    }

  private:
    std::map< std::string, dycore_field< data_store_t > > fields_;
};
