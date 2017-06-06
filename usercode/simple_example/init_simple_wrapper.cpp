#include "my_simple_wrapper.h"
#include "../../wrapper/include/init_simple_wrapper.h"

wrappable *init_simple_wrapper() { return new my_simple_wrapper(); }
void destroy_simple_wrapper(wrappable *m) { delete m; }
