#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../../wrapper/include/wrapper_functions.h"

int main() {
    printf("main()\n");
    struct wrapper_map *my_map = init_wrapper_map();

    float *tmp = (float *)malloc(sizeof(float));
    *tmp = 3.1415;
    bool do_a_copy = true;
    push(my_map, "testfield", tmp, do_a_copy);
    float *result;
    result = pull(my_map, "testfield");
    printf("%f\n", *result);
    result = pull(my_map, "testfield_non_existent");
}
