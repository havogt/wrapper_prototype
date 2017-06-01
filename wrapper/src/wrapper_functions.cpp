#include "wrapper_functions.h"
#include <iostream>
#include <vector>

namespace internal {
    std::vector< int > make_dim_vector(int ndims, int *dims) {
        std::vector< int > v_dims(ndims);
        for (size_t i = 0; i < ndims; ++i) {
            v_dims[i] = dims[i];
        }
        return v_dims;
    }
}

bool same_layout(/**/) { return false; }

void push(wrappable *m, char *name, float *ptr, int ndims, int *dims, int *strides, bool force_copy) {
    std::cout << "push for " << std::string(name) << " with src ptr " << ptr << std::endl;
    raw_storage storage = m->get_raw_storage_for_push(name, internal::make_dim_vector(ndims, dims));
    if (!force_copy && same_layout()) {
        std::cout << "We have the same layout we do ptr sharing mode" << std::endl;
        //        m->set_external_ptr(name, ptr); TODO
    } else {

        // TODO Do the copy based on the layout
    }
}

void pull(wrappable *m, char *name, float *ptr, int ndims, int *dims, int *strides) {
    std::cout << "pull for " << std::string(name) << " to ptr " << ptr << std::endl;
    raw_storage storage = m->get_raw_storage_for_pull(name, internal::make_dim_vector(ndims, dims));
    if (ptr == (float *)storage.ptr) {
        // We are in ptr sharing mode
        // this case can be removed as it does nothing
    } else {
        // TODO do the copy back
    }
}

void call_do_step(wrappable *m) {
    std::cout << "call_do_step()" << std::endl;
    m->do_step();
}
