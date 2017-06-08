#include "Dycore.h"
#include "wrapper_functions.h"

static wrappable *create_dycore() { return new DycoreWrapper(); }
static bool registered = register_wrapper_factory("dycore", create_dycore);
