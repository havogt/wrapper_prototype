#pragma once

#include <iostream>
#include <map>
#include <string>

#include <storage/storage-facility.hpp>
#include "../../wrapper/include/wrapper_handler.h"

// setup gridtools storage types
using namespace gridtools;
using namespace gridtools::enumtype;

using storage_info_t = storage_traits< Host >::storage_info_t< 0, 3 >;
using data_store_t = storage_traits< Host >::data_store_t< float_type, storage_info_t >;

class dycore : public wrappable {
  public:
    dycore() : meta_data_(5, 6, 7) {}

    raw_storage get_raw_storage(std::string name) {
        int *dims = new int[3]{2, 3, 4}; // TODO nice ctor to remove that leak
        int *strides = new int[3]{1, 2, 6};

        raw_storage my_storage{nullptr, 3, dims, strides};

        return my_storage;
    }

    //    void DoStep(output(), input(u), constant()) {
    //        if (!input_clean(input))
    //            error();
    //        flag_output_dirty(output);
    //
    //        // Do stuff
    //
    //        flag_input_dirty(input);
    //    }

  private:
    storage_info_t meta_data_;
    std::map< std::string, data_store_t > fields;
};
