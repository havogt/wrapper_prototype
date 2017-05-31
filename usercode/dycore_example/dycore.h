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

class dycore : public wrapper_handler {
  public:
    dycore() : meta_data_(5, 6, 7) {}

    void push(/*std::string name, layout_t src_layout, ptr data, */) {
        std::cout << "dycore received a push" << std::endl;

        // TODO need to check if storage_info_t layout fits to the one coming in
        //
        // TODO do the copy
    }
    void pull() { std::cout << "dycore received a pull" << std::endl; }

    /*
    layout_plus_dst get_destination( std::string name )
    {
        return {get_layout(meta_data_), fields["name"]};
    }
    void set_pointer_of_storage(void* ptr) {}
    */

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
    //        data_store_t u;
    //    data_store_t v;
};
