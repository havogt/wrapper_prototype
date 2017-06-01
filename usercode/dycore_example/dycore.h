#pragma once

#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#include <storage/storage-facility.hpp>
#include "../../wrapper/include/wrappable.h"
#include "dycore_helper.h"

/**
 * This is just an example to attach to state flags to the storage to allow a consistency check between fortran and cpp
 */
template < typename DataStore >
struct dycore_field {
    bool cpp_is_uptodate;
    bool fortran_is_uptodate;
    DataStore field;
};

class dycore : public wrappable {
  public:
    /**
     * This function needs to be provided by a user of the gridtools wrapper
     * @param name Field name
     * @param dims Dimensions of the field coming from the wrapper, can be used to initialize a gridtools fields.
     */
    raw_storage get_raw_storage_for_push(std::string name, std::vector< int > dims) {
        if (fields.count(name) == 0) {
            // field was not pushed before

            // Here it is the dycore responsibility how to handle fields (map, explicit types via a switch on the
            // fieldname, etc...)
            // I chose the map in this example as it is simplest
            storage_info_t meta_data(dims[0], dims[1], dims[2]);
            fields.emplace(name, dycore_field< data_store_t >{true, true, data_store_t(meta_data, name)});
            std::cout << "initialized a new gridtools field \"" << name << "\"" << std::endl;
        } else {
            // field is already initialized: validate our copy
            fields[name].cpp_is_uptodate = true;
            std::cout << "\"" << name << " is already initialized; returning its info" << std::endl;
        }

        return make_raw_storage(fields[name]);
    }

    /**
    * This function needs to be provided by a user of the gridtools wrapper
    */
    raw_storage get_raw_storage_for_pull(std::string name, std::vector< int > dims) {
        if (fields.count(name) == 0) {
            throw std::runtime_error("field is not initialized, cannot  pull");
        } else {
            std::cout << "\"" << name << " is initialized; returning its info" << std::endl;
            fields[name].fortran_is_uptodate = true;
        }

        return make_raw_storage(fields[name]);
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

    bool check_cpp_fields_uptodate() {
        bool uptodate = true;
        for (auto &field : fields) {
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
        for (auto &field : fields) {
            uptodate = uptodate && field.second.fortran_is_uptodate;
        }
        return uptodate;
    }

    void do_step() {
        std::cout << "Calling DoStep(input, output)" << std::endl;

        DoStep(input(fields["some_input"], fields["some_input"]), output(fields["some_output"]));
    }

  private:
    storage_info_t meta_data_;
    std::map< std::string, dycore_field< data_store_t > > fields;
};
