#include "modules/modules.hpp"
#include <dynlib.hpp>
#include <iostream>

int main() {
  // Attempt to load the dynamic library "./external_module.so" and get a handle
  // to it.
  auto _handle = DynamicLibrary::getLib("./external_module.so");

  // Try to retrieve the module from the loaded library.
  // If the module is not found, use the default module provided by
  // default_module.
  Module _mod = DynamicLibrary::getModule(_handle, &default_module);

  // Retrieve the function pointer to the function named "_foo_m" from the
  // module.
  foo_ptr f = _mod._foo_m;

  // Obtain the addresses of the retrieved function and the default function
  // "_bar_m".
  int *addr1 = (int *)f;
  int *addr2 = (int *)default_module._bar_m;

  // Print the addresses of the current function and the default function.
  printf("Current function address %p\n", f);
  printf("Default function address %p\n", default_module._bar_m);

  // Call the function pointer "f" with arguments 1234 and 1 and print the
  // result.
  std::cout << f(1234, 1) << std::endl;
  return (f(1, 1) == 20) ? 0 : -1;
}
