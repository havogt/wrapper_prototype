#include "wrapper_functions.h"
#include <iostream>
#include <vector>
#include <map>

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

int call(wrappable *h, const char *action) { h->call(std::string(action)); }

/**
 * @brief Getter to obtain the wrapper factories. Due to the static initialization order this
 *        object cannot be stored statically: https://isocpp.org/wiki/faq/ctors#static-init-order
 *
 * @return The map containing the wrapper factories it is a map mapping a string to a function
 *         pointer which acts as a factory.
 */
std::map< std::string, std::function< wrappable *() > > &get_wrapper_factories() {
    static std::map< std::string, std::function< wrappable *() > > map;
    return map;
}

/**
 * @brief Register a wrappable factory with the wrapper
 * @param name of the factory
 * @param function pointer to the factory
 * @return Dummy argument for static registration
 */
bool register_wrapper_factory(std::string name, std::function< wrappable *() > func) {
    std::cout << "Debug: Register wrapper factory with " << name << " )\n";
    get_wrapper_factories()[name] = func;
    return true;
}

wrappable *create_wrapper(const char *name) {
    const auto namestr = std::string(name);
    auto &factories = get_wrapper_factories();
    if (factories.find(namestr) == factories.end()) {

        throw std::runtime_error("create_wrapper: Wrapper with name " + namestr + " is not registered.");
    }
    return factories[namestr]();
}

void destroy_wrapper(wrappable *m) { delete m; }
