#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../../wrapper/include/wrapper_functions.h"
#include "dycore_init.h"

int main() {
    printf("main()\n");

    int Ni = 2;
    int Nj = 3;
    int Nk = 4;

    int total_size = Ni * Nj * Nk;

    float *my_field = (float *)malloc(total_size * sizeof(float));

    struct wrappable *dycore = init_dycore();

    int ndim = 3;
    int dims[3] = {Ni, Nj, Nk};
    int strides[3] = {1, 2, 6};

    push(dycore, "some_output", my_field, ndim, dims, strides, false);
    printf("---------------------\n");

    push(dycore, "some_input", my_field, ndim, dims, strides, false);
    printf("---------------------\n");
    push(dycore, "some_input", my_field, ndim, dims, strides, false);
    printf("---------------------\n");

    call_do_step(dycore);

    printf("---------------------\n");
    if (!check_fortran_fields_uptodate(dycore)) {
        printf("fortran fields are not up-to-date :(\n");
    } else {
        printf("fortran fields are uptodate. NICE!\n");
    }

    pull(dycore, "some_output", my_field, ndim, dims, strides);
    printf("---------------------\n");
    if (!check_fortran_fields_uptodate(dycore)) {
        printf("fortran fields are not up-to-date :(\n");
    } else {
        printf("fortran fields are uptodate. NICE!\n");
    }

    destroy_dycore(dycore);
}
