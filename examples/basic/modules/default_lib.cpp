#include "modules.hpp" 
#include <dynlib/dyn_module.hpp>

// Declaration and implementation of default_foo function which returns the sum of its two arguments.
int default_foo(int a, int b) { return a + b; }

// Declaration and implementation of default_bar function which returns the product of its argument and 16.
int default_bar(int a) { return a * 16; }

#ifdef DEFAULT_MODULE
// If DEFAULT_MODULE is defined, create a Module object named default_module
// containing pointers to default_foo and default_bar functions.
EXPORT_MODULE(default_module,&default_foo, &default_bar);
#else
EXPORT_MODULE(module,&default_foo, &default_bar);
#endif 
