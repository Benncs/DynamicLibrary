#include "dynlib/dyn_module.hpp"
#include "modules.hpp"

// It's possible to declare "private" functions.
int baz() { return 10; }

// Declaration and implementation of the function to be exported.
int foo(int a, int b) { return baz() * (a + b); }

int bar(int a) { return a * 16 * 2; }

// Don't forget to export the module.
EXPORT_MODULE(module) = {._foo_m = &foo, ._bar_m = &bar};

/* We could define the default module as described in modules.hpp,
but in our case, this external module will never be used as a default module,
so the definition doesn't exist. */
