#pragma once

#ifdef __cplusplus
#include "wrappable.h"
#define C_STRUCT_KEYWORD
extern "C" {
#else
struct wrappable;
#define C_STRUCT_KEYWORD struct
#endif

void push(C_STRUCT_KEYWORD wrappable *h, char *name, float *ptr, int ndims, int *dims, int *strides, bool copy);
void pull(C_STRUCT_KEYWORD wrappable *h, char *name, float *ptr, int ndims, int *dims, int *strides);
void call_do_step(C_STRUCT_KEYWORD wrappable *h);

#ifdef __cplusplus
}
#endif

#undef C_STRUCT_KEYWORD
