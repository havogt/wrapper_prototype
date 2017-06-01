#include "dycore_init.h"
#include "dycore.h"
#include <iostream>

wrappable *init_dycore() { return new dycore(); }

void destroy_dycore(wrappable *m) { delete m; }

bool check_fortran_fields_uptodate(wrappable *m) {
    dycore *dycore_ptr = (dycore *)m;
    return dycore_ptr->check_fortran_fields_uptodate();
}
