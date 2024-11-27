#include "module_advanced.hpp"
#include "dynlib/dyn_module.hpp"
#include <iostream>

struct impl {
  int a;
};

void _init_udf(impl &pimpl, int a) {
  std::cout << "internal.a=" << pimpl.a << std::endl;
  std::cout << "arg=" << a << std::endl;
}

void _make_udf(Model &model) {
  model.pimpl = new impl;
  model.pimpl->a = 11212024;
}

void _delete_udf(impl **pimpl) {
  if (pimpl != nullptr) {
    delete *pimpl;
    *pimpl = nullptr;
  }
}

// Don't forget to export the module.
EXPORT_MODULE(module) = {&_init_udf, &_make_udf, &_delete_udf};
