#pragma once
#include <map>
#include "wrapper_handler.h"

struct wrapper_element {
    float *ptr;
    bool copy;
};

class wrapper_map {
  public:
    std::map< std::string, wrapper_element > field_map;
    wrapper_handler *handle;
};
