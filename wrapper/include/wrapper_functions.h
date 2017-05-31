#pragma once

#ifdef __cplusplus
#include "wrapper_map.hpp"
#include "wrapper_handler.h"
#define C_STRUCT_KEYWORD
extern "C" {
#else
struct wrapper_map;
struct wrapper_handler;
#define C_STRUCT_KEYWORD struct
#endif

C_STRUCT_KEYWORD wrapper_map *init_wrapper_map();
void destroy_wrapper_map(C_STRUCT_KEYWORD wrapper_map *);

void push(C_STRUCT_KEYWORD wrapper_map *m, char *name, float *ptr, bool copy);
float *pull(C_STRUCT_KEYWORD wrapper_map *m, char *name);
void set_handler(C_STRUCT_KEYWORD wrapper_map *m, C_STRUCT_KEYWORD wrapper_handler *h);

#ifdef __cplusplus
}
#endif

#undef C_STRUCT_KEYWORD
