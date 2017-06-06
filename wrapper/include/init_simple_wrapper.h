#pragma once

#ifdef __cplusplus
#define C_STRUCT_KEYWORD
#include "wrappable.h"
extern "C" {
#else
struct wrappable;
#define C_STRUCT_KEYWORD struct
#endif

C_STRUCT_KEYWORD wrappable *init_simple_wrapper();
void destroy_simple_wrapper(C_STRUCT_KEYWORD wrappable *);

#ifdef __cplusplus
}
#endif

#undef C_STRUCT_KEYWORD
