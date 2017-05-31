#include "wrapper_functions.h"
#include <iostream>

bool same_layout(/**/) { return false; }

void push(wrappable *m, char *name, float *ptr, bool force_copy) {
    std::cout << "push for " << std::string(name) << " with src ptr " << ptr << std::endl;
    raw_storage storage = m->get_raw_storage(name);
    if (!force_copy && same_layout()) {
        std::cout << "We have the same layout we do ptr sharing mode" << std::endl;
        //        m->set_external_ptr(name, ptr); TODO
    } else {
        // TODO Do the copy based on the layout
    }
}

void pull(wrappable *m, char *name, float *ptr) {
    std::cout << "pull for " << std::string(name) << " to ptr " << ptr << std::endl;
    raw_storage storage = m->get_raw_storage(name);
    if (ptr == (float *)storage.ptr) {
        // We are in ptr sharing mode
        // this case can be removed as it does nothing
    } else {
        // TODO do the copy back
    }
}
