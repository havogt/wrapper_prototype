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

    void copy(float *dst, float *src, abstract_storage_info info) {
        // do it
    }

    bool same_layout(abstract_storage_info info, int ndims, int *dims, int *strides) { return false; }
}

void push(wrappable *m, char *name, float *ptr, int ndims, int *dims, int *strides, bool force_copy) {
    std::cout << "push for " << std::string(name) << " with src ptr " << ptr << std::endl;
    auto dims_vector = internal::make_dim_vector(ndims, dims);
    abstract_storage_info info = m->get_abstract_storage_info(name, dims_vector);

    bool external_ptr_mode = !force_copy && internal::same_layout(info, ndims, dims, strides);
    m->init_optional(name, dims_vector, external_ptr_mode, ptr); // ptr can be nullptr if !external_ptr_mode

    float *dst_ptr = (float *)m->get_pointer(name);

    if (dst_ptr != ptr) {
        internal::copy(dst_ptr, ptr, info);
    }
    m->notify_push(name);
}

void pull(wrappable *m, char *name, float *ptr, int ndims, int *dims, int *strides) {
    std::cout << "pull for " << std::string(name) << " to ptr " << ptr << std::endl;

    float *src_ptr = (float *)m->get_pointer(name);
    if (src_ptr == nullptr) {
        throw std::runtime_error("Field is not available for pull");
    } else {
    }

    if (ptr == src_ptr) {
        // We are in ptr sharing mode: do nothing
    } else {
        internal::copy(ptr, src_ptr, m->get_abstract_storage_info(name, internal::make_dim_vector(ndims, dims)));
    }

    m->notify_pull(name);
}

void call_do_step(wrappable *m) {
    std::cout << "call_do_step()" << std::endl;
    m->do_step();
}
