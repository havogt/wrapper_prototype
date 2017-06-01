#pragma once

#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#include <storage/storage-facility.hpp>
#include "../../wrapper/include/wrappable.h"

// setup gridtools storage types
using namespace gridtools;
using namespace gridtools::enumtype;

using storage_info_t = storage_traits< Host >::storage_info_t< 0, 3 >;
using data_store_t = storage_traits< Host >::data_store_t< float_type, storage_info_t >;

template < typename DataStore >
struct dycore_field {
    bool cpp_is_uptodate;
    bool fortran_is_uptodate;
    DataStore field;
};

class dycore : public wrappable {
  public:
    dycore() : meta_data_(5, 6, 7) {}

    /**
     * @param name Field name
     * @param dims Dimensions of the field coming from the wrapper, can be used to initialize a gridtools fields.
     */
    raw_storage get_raw_storage_for_push(std::string name, std::vector< int > dims) {
        if (fields.count(name) == 0) {
            // TODO fix this in gridtools: allow a vector/array of dims
            storage_info_t meta_data(dims[0], dims[1], dims[2]);
            fields.emplace(name, dycore_field< data_store_t >{true, true, data_store_t(meta_data, name)});
            std::cout << "initialized a new gridtools field \"" << name << "\"" << std::endl;
        } else {
            fields[name].cpp_is_uptodate = true;
            std::cout << "\"" << name << " is already initialized; returning its info" << std::endl;
        }

        // TODO use the field to produce this (currently fake) information
        int *gt_dims = new int[3]{2, 3, 4}; // TODO nice ctor to remove that leak
        int *gt_strides = new int[3]{1, 2, 6};

        raw_storage my_storage{nullptr, 3, gt_dims, gt_strides};

        return my_storage;
    }

    raw_storage get_raw_storage_for_pull(std::string name, std::vector< int > dims) {
        if (fields.count(name) == 0) {
            throw std::runtime_error("field is not initialized, cannot  pull");
        } else {
            std::cout << "\"" << name << " is initialized; returning its info" << std::endl;
            fields[name].fortran_is_uptodate = true;
        }

        // TODO use the field to produce this (currently fake) information
        int *gt_dims = new int[3]{2, 3, 4}; // TODO nice ctor to remove that leak
        int *gt_strides = new int[3]{1, 2, 6};

        raw_storage my_storage{nullptr, 3, gt_dims, gt_strides};

        return my_storage;
    }

    // TODO this is just a placeholder for the input/output pattern which is not part of this design
    void DoStep(dycore_field< data_store_t > &input, dycore_field< data_store_t > &output) {
        // check that all fields are uptodate in cpp
        if (!check_cpp_fields_uptodate())
            std::cout << "a cpp field is not up-to-date." << std::endl;
        else
            std::cout << "all fields are up-to-date. NICE!" << std::endl;

        // invalidate the output on the fortran side as we are going to change it!
        output.fortran_is_uptodate = false;

        // Do the great timestep

        // invalidate all input fields as they are now consumed and should be updated in fortran
        input.cpp_is_uptodate = false;
    }

    bool check_cpp_fields_uptodate() {
        bool uptodate = true;
        for (auto &field : fields) {
            uptodate = uptodate && field.second.cpp_is_uptodate;
        }
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
        DoStep(fields["some_input"], fields["some_output"]);
    }

  private:
    storage_info_t meta_data_;
    std::map< std::string, dycore_field< data_store_t > > fields;
};
