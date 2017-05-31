#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../../wrapper/include/wrapper_functions.h"
#include "dycore_init.h"

/* TODO
 * - flag on each field which is modified by the input()/output() parameters and the push/pull automatically
 * - check in the dycore that all input fields are clean at the beginning, invalidate all inputs at the end()
 * - invalidate all output fields in the dycore
 * - the dycore provides a function to fortran to check if all clean after pull
 * - usercode returns a layout+raw_ptr to the wrapper to allow the wrapper to do its copies.
 */

int main() {
    printf("main()\n");
    float *tmp = (float *)malloc(sizeof(float));

    struct wrappable *dycore = init_dycore();

    push(dycore, "some_field", tmp, false);
    pull(dycore, "some_field", tmp);

    destroy_dycore(dycore);
}
