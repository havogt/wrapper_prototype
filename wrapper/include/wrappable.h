#pragma once
#include <string>
#include <vector>

struct raw_storage {
    void *ptr;
    int ndims;
    int *dims; // TODO smart ptrs
    int *strides;
};

class wrappable {
  public:
    virtual raw_storage get_raw_storage_for_push(std::string name, std::vector< int >) = 0;
    virtual raw_storage get_raw_storage_for_pull(std::string name, std::vector< int >) = 0;
    virtual void do_step() = 0;
};
