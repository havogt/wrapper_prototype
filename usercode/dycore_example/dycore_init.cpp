#include "dycore_init.h"
#include "dycore.h"
#include <iostream>

wrappable *init_dycore() { return new dycore(); }

void destroy_dycore(wrappable *m) { delete m; }
