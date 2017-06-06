#pragma once
#include <string>
#include <vector>

struct raw_storage {
    bool initialized;
    void *ptr;
    int *strides;
};

struct abstract_storage_info {
    int ndims;
    int *dims;
    int *strides;
};

template < typename StorageInfo >
abstract_storage_info make_abstract_storage_info(const StorageInfo &info) {
    // TODO use the field to produce this (currently fake) information
    int *gt_dims = new int[3]{2, 3, 4}; // TODO nice ctor to remove that leak
    int *gt_strides = new int[3]{1, 2, 6};

    abstract_storage_info abstract_info{3, gt_dims, gt_strides};
    return abstract_info;
}

class wrappable {
  public:
    virtual abstract_storage_info get_abstract_storage_info(std::string name, std::vector< int > dims) = 0;
    virtual void init_optional(std::string name, std::vector< int > dims, bool external_ptr, void *ptr) = 0;
    virtual void *get_pointer(std::string name) = 0;
    virtual void notify_push(std::string name) = 0;
    virtual void notify_pull(std::string name) = 0;

    virtual void do_step() = 0;
};
