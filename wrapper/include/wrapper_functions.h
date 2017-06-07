#pragma once
#ifdef __cplusplus
#include "wrappable.h"
extern "C" {
#else
typedef struct wrappable {} wrappable;
#endif

wrappable* create_wrapper(const char* name);
void push(wrappable *h, char *name, float *ptr, int ndims, int *dims, int *strides, bool copy);
void pull(wrappable *h, char *name, float *ptr, int ndims, int *dims, int *strides);
int call(wrappable *h, const char* action);
int destroy_wrapper(wrappable* m);
#ifdef __cplusplus
}

#include <string>
#include <functional>
bool register_wrapper_factory(std::string name, std::function<wrappable*()> func);
#endif

#undef C_STRUCT_KEYWORD
