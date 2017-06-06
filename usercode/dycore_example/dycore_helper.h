#pragma once

template < typename... F >
std::tuple< F &&... > input(F &&... f) {
    return std::forward_as_tuple(f...);
}

template < typename... F >
std::tuple< F &&... > output(F &&... f) {
    return std::forward_as_tuple(f...);
}

template < typename F, typename... Args >
void for_each_argument(F f, Args &&... args) {
    [](...) {}((f(std::forward< Args >(args)), 0)...);
}

template < typename F, typename Tuple >
void for_each_in_tuple(F f, Tuple &&tuple) {
    std::apply([f](auto &&... args) { for_each_argument(f, args...); }, tuple);
}

// setup gridtools storage types
using namespace gridtools;
using namespace gridtools::enumtype;

using storage_info_t = storage_traits< Host >::storage_info_t< 0, 3 >;
using data_store_t = storage_traits< Host >::data_store_t< float_type, storage_info_t >;
