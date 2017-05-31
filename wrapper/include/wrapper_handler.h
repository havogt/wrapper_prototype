#pragma once
#include <string>

struct raw_storage {
    void *ptr;
    int ndims;
    int *dims; // TODO smart ptrs
    int *strides;
};

class wrappable {
  public:
    virtual raw_storage get_raw_storage(std::string name) = 0;
};
