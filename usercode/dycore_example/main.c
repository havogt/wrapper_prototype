#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../../wrapper/include/wrapper_functions.h"

int main() {
    printf("main()\n");

    int Ni = 2;
    int Nj = 3;
    int Nk = 4;

    int total_size = Ni * Nj * Nk;

    float *my_field = (float *)malloc(total_size * sizeof(float));

    struct wrappable *dycore = gt_wrapper_create("dycore");

    int ndim = 3;
    int dims[3] = {Ni, Nj, Nk};
    int strides[3] = {1, 2, 6};

    gt_wrapper_push(dycore, "some_output", my_field, ndim, dims, strides, false);
    printf("---------------------\n");

    gt_wrapper_push(dycore, "some_input", my_field, ndim, dims, strides, false);
    printf("---------------------\n");
    gt_wrapper_push(dycore, "some_input", my_field, ndim, dims, strides, false);
    printf("---------------------\n");

    gt_wrapper_call(dycore, "init");
    gt_wrapper_call(dycore, "DoStep");

    printf("---------------------\n");
    if (gt_wrapper_call(dycore, "check_fortran_fields_uptodate") == 0) {
        printf("fortran fields are not up-to-date: That is expected! NICE!(\n");
    } else {
        printf("fortran fields are uptodate, but they shouldn't: NOT NICE!\n");
    }

    gt_wrapper_pull(dycore, "some_output", my_field, ndim, dims, strides);
    printf("---------------------\n");
    if (gt_wrapper_call(dycore, "check_fortran_fields_uptodate") == 0) {
        printf("fortran fields are not up-to-date: NOT NICE!(\n");
    } else {
        printf("fortran fields are uptodate. NICE!\n");
    }

    gt_wrapper_destroy(dycore);
}
