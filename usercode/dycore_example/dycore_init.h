#pragma once

#ifdef __cplusplus
#include "dycore.h"
#define C_STRUCT_KEYWORD
extern "C" {
#else
struct wrapper_handler;
#define C_STRUCT_KEYWORD struct
#endif

C_STRUCT_KEYWORD wrapper_handler *init_dycore();
void destroy_dycore(C_STRUCT_KEYWORD wrapper_handler *);

#ifdef __cplusplus
}
#endif

#undef C_STRUCT_KEYWORD
