#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../../wrapper/include/wrapper_functions.h"
#include "dycore_init.h"

int main() {
    printf("main()\n");
    float *tmp = (float *)malloc(sizeof(float));

    struct wrapper_map *wrapper_object = init_wrapper_map();
    struct wrapper_handler *dycore = init_dycore();

    set_handler(wrapper_object, dycore);

    push(wrapper_object, "some_field", tmp, false);
    pull(wrapper_object, "some_field");

    destroy_wrapper_map(wrapper_object);
    destroy_dycore(dycore);
}
