#include "modules.hpp"

// It's possible to declare "private" functions.
int baz() { return 10; }

// Declaration and implementation of the function to be exported.
int foo(int a, int b) { return baz() * (a + b); }

int bar(int a) { return a * 16 * 2; }

//function defined but not exported 