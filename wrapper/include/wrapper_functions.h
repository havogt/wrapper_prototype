#pragma once
#ifdef __cplusplus
#include "wrappable.h"
extern "C" {
#else
typedef struct wrappable {
} wrappable;
#endif

wrappable *gt_wrapper_create(const char *name);
void gt_wrapper_destroy(wrappable *m);

void gt_wrapper_push(wrappable *h, char *name, float *ptr, int ndims, int *dims, int *strides, bool copy);
void gt_wrapper_pull(wrappable *h, char *name, float *ptr, int ndims, int *dims, int *strides);

int gt_wrapper_call(wrappable *h, const char *action);
int gt_wrapper_call_proc(wrappable *h, const char *action, void *data);
// MAYBE:
// int call(wrappable *h, const char *action, int data);
// int call(wrappable *h, const char *action, char *data);
// int call(wrappable *h, const char *action, double data);
// int call(wrappable *h, const char *action, float data);

#ifdef __cplusplus
}

#include <string>
#include <functional>
bool register_wrapper_factory(std::string name, std::function< wrappable *() > func);
#endif

#undef C_STRUCT_KEYWORD
