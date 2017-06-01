#pragma once

#ifdef __cplusplus
#include "dycore.h"
#define C_STRUCT_KEYWORD
extern "C" {
#else
struct wrappable;
struct dycore;
#define C_STRUCT_KEYWORD struct
#endif

C_STRUCT_KEYWORD wrappable *init_dycore();
void destroy_dycore(C_STRUCT_KEYWORD wrappable *);
bool check_fortran_fields_uptodate(C_STRUCT_KEYWORD wrappable *);

#ifdef __cplusplus
}
#endif

#undef C_STRUCT_KEYWORD
