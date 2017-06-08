#pragma once
#include <string>
#include <vector>

#define WRAPPER_RETURN_SUCCESS 1
#define WRAPPER_RETURN_FAILURE 0

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
    virtual ~wrappable() = default;

    virtual abstract_storage_info get_abstract_storage_info(const std::string &name, std::vector< int > dims) = 0;
    virtual void init(const std::string &name, std::vector< int > dims, bool external_ptr, void *ptr) = 0;
    virtual void *get_pointer(const std::string &name) = 0;
    virtual void notify_push(const std::string &name) = 0;
    virtual void notify_pull(const std::string &name) = 0;
    virtual bool is_initialized(const std::string &name) = 0;
    virtual void set_external_pointer(const std::string &name, float *ptr) = 0;

    virtual int call(const std::string &action) { return -1; };
    virtual int call(const std::string &action, void *ptr) { return -1; };
};
