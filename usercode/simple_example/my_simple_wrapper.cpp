/**
 *
 */
#include "my_simple_wrapper.h"
#include <wrapper_functions.h>

void my_simple_wrapper::do_step() { std::cout << "do_step()" << std::endl; }

wrappable* my_simple_wrapper_factory() {
    return new my_simple_wrapper();
}
static bool simple_wrapper_registered = register_wrapper_factory("my_simple_wrapper", my_simple_wrapper_factory);
