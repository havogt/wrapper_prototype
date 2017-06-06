#pragma once
#include <storage/storage-facility.hpp>
#include "../../wrapper/include/simple_wrapper.h"

using storage_info_t = gridtools::storage_traits< gridtools::enumtype::Host >::storage_info_t< 0, 3 >;
using data_store_t = gridtools::storage_traits< gridtools::enumtype::Host >::data_store_t< float, storage_info_t >;

class my_simple_wrapper : public simple_wrapper< data_store_t > {
  public:
    void do_step();
};
