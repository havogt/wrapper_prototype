#include "wrapper_functions.h"
#include <iostream>

wrapper_map *init_wrapper_map() {
    wrapper_map *my_wrapper_map = new wrapper_map();
    return my_wrapper_map;
}

void destroy_wrapper_map(wrapper_map *m) { delete m; }

void push(wrapper_map *m, char *name, float *ptr, bool copy) {
    m->field_map[std::string(name)] = wrapper_element{ptr, copy};
    std::cout << "added " << std::string(name) << " with src ptr " << ptr << std::endl;
    m->handle->push();
}

float *pull(wrapper_map *m, char *name) {
    if (m->field_map.count(std::string(name)) > 0) {
        wrapper_element elem = m->field_map.at(std::string(name));
        std::cout << "pulling " << std::string(name) << " with ptr " << elem.ptr << std::endl;
        if (elem.copy) {
            std::cout << "   have to copy..." << std::endl;
        }
        m->handle->pull();
        return elem.ptr;
    } else {
        std::cout << "field " << std::string(name) << " does not exist!" << std::endl;
        return NULL;
    }
}

void set_handler(wrapper_map *m, wrapper_handler *h) { m->handle = h; }
