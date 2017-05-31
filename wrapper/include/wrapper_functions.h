#pragma once

#ifdef __cplusplus
#include "wrapper_handler.h"
#define C_STRUCT_KEYWORD
extern "C" {
#else
struct wrappable;
#define C_STRUCT_KEYWORD struct
#endif

// C_STRUCT_KEYWORD wrapper_map *init_wrapper_map();
// void destroy_wrapper_map(C_STRUCT_KEYWORD wrapper_map *);

void push(C_STRUCT_KEYWORD wrappable *h, char *name, float *ptr, bool copy);
void pull(C_STRUCT_KEYWORD wrappable *h, char *name, float *ptr);
// void set_handler(C_STRUCT_KEYWORD wrapper_map *m, C_STRUCT_KEYWORD wrapper_handler *h);

#ifdef __cplusplus
}
#endif

#undef C_STRUCT_KEYWORD
