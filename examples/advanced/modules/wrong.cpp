
#include "modules.hpp"
#include <iostream>

struct impl {
  int a;
};

void _init_udf(impl &pimpl, int a) {
  std::cout << "A=" << pimpl.a << std::endl;
}

void _make_udf(Model &model) {
  model.pimpl = new impl;
  model.pimpl->a = 56;
}

void _delete_udf(impl **pimpl) {
  if (pimpl != nullptr) {
    delete *pimpl;
    *pimpl = nullptr;
  }
}

// Don't forget to export the module.
// Module module = {&_init_udf, &_make_udf, &_delete_udf};
