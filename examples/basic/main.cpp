#include "modules/modules.hpp"
#include <dynlib/dynlib.hpp>
#include <iostream>

int exec(std::shared_ptr<DynamicLibrary> handle) {
  // Try to retrieve the module from the loaded library.
  // If the module is not found, use the default module provided by
  // default_module.
  Module _mod = DynamicLibrary::getModule(handle, &default_module);

  // Retrieve the function pointer to the function named "_foo_m" from the
  // module.
  foo_ptr f = _mod._foo_m;

  // Print the addresses of the current function and the default function.
  std::cout << "Current function address " << (void *)f << std::endl;
  std::cout << "Default function address " << (void *)default_module._foo_m
            << std::endl;

  if (f == default_module._foo_m) {
    std::cout << "Using default implementation" << std::endl;
  }
  // Call the function pointer "f" with arguments 1234 and 1 and print the
  // result.
  std::cout << f(1234, 1) << std::endl;
  return (f(1, 1) == 20) ? 0 : -1;
}

int main(int argc, char **argv) {

  std::shared_ptr<DynamicLibrary> _handle;

  if (argc == 2) {
    std::cout << "Loading " << argv[1] << std::endl;
    _handle = DynamicLibrary::getLib(argv[1]);
  }

  return exec(_handle);
}
