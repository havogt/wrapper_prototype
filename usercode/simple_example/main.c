#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../../wrapper/include/wrapper_functions.h"

int main() {
    printf("main()\n");

    wrappable *my_wrapper = gt_wrapper_create("my_simple_wrapper");

    float *tmp = (float *)malloc(sizeof(float));
    *tmp = 3.1415;

    int dim = 3;
    int *dims = (int *)malloc(sizeof(int) * dim);
    dims[0] = 4;
    dims[1] = 5;
    dims[2] = 6;
    int *strides = (int *)malloc(sizeof(int) * dim);

    gt_wrapper_push(my_wrapper, "testfield", tmp, dim, dims, strides, 0);
    gt_wrapper_push(my_wrapper, "testfield", tmp, dim, dims, strides, 0);
    gt_wrapper_push(my_wrapper, "testfield", tmp, dim, dims, strides, 1);
//    pull(my_wrapper, "non_existent_field", tmp, dim, dims, strides);

    gt_wrapper_destroy(my_wrapper);
}
