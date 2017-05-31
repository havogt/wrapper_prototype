#include "dycore_init.h"
#include "dycore.h"
#include <iostream>

wrapper_handler *init_dycore() { return new dycore(); }

void destroy_dycore(wrapper_handler *m) { delete m; }
