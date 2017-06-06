#pragma once

#include <iostream>
#include <map>
#include <stdexcept>
#include <string>

#include "wrappable.h"

/**
 * Simple wrapper for an application with only one field type.
 * The user needs to provide an implementation of the do_step (which should get a more general name).
 */

/**
 * This function should be provided by the gridtools storage
 */
template < typename DataStore >
raw_storage make_raw_storage(const DataStore &field) {
    // TODO use the field to produce this (currently fake) information
    int *gt_dims = new int[3]{2, 3, 4}; // TODO nice ctor to remove that leak
    int *gt_strides = new int[3]{1, 2, 6};

    raw_storage my_storage{nullptr, 3, gt_dims, gt_strides};
}

template < typename DataStoreType >
class simple_wrapper {};

template < template < typename, typename > class DataStore, typename Storage, typename StorageInfo >
class simple_wrapper< DataStore< Storage, StorageInfo > > : public wrappable {
  public:
    using data_store_t = DataStore< Storage, StorageInfo >;

    abstract_storage_info get_abstract_storage_info(std::string name, std::vector< int > dims) override {
        return make_abstract_storage_info(StorageInfo(dims[0], dims[1], dims[2])); // TODO generalize dims
    }

    void init_optional(std::string name, std::vector< int > dims, bool external_ptr, void *ptr) override {
        if (fields.count(name) == 0) {
            StorageInfo meta_data(dims[0], dims[1], dims[2]);
            if (external_ptr) {
                fields.emplace(name,
                    data_store_t(meta_data,
                                   (float *)ptr,
                                   gridtools::ownership::ExternalCPU,
                                   name)); // TODO: ownership?, TODO: datatype
                std::cout << "initialized a new gridtools field in pointer sharing mode" << std::endl;
            } else {
                fields.emplace(name, data_store_t(meta_data, name));
                std::cout << "initialized a new gridtools field" << std::endl;
            }
        }
    }

    void *get_pointer(std::string name) override {
        if (fields.count(name) > 0) {
            return (void *)fields[name].get_storage_ptr()->get_cpu_ptr();
        } else
            return nullptr;
    }

    void notify_push(std::string name) override{};
    void notify_pull(std::string name) override{};

    virtual void do_step() = 0;

  private:
    std::map< std::string, data_store_t > fields;
};
