#pragma once
#include <storage/storage-facility.hpp>
#include "../../wrapper/include/simple_wrapper.h"

using storage_info_t = gridtools::storage_traits< gridtools::enumtype::Host >::storage_info_t< 0, 3 >;
using data_store_t = gridtools::storage_traits< gridtools::enumtype::Host >::data_store_t< float, storage_info_t >;

class my_simple_wrapper : public simple_wrapper< data_store_t > {
  public:
    my_simple_wrapper() = default;
    virtual ~my_simple_wrapper() = default;

    virtual int call(const std::string &action) override {
        std::cout << "My simple wrapper received call to do: " << action << "\n";
        if (action == "do_step") {
            do_step();
            return WRAPPER_RETURN_SUCCESS;
        }
        std::cout << "Action " << action << " is not known\n";
        return WRAPPER_RETURN_FAILURE;
    }
    void do_step();
};
