#include "modules.hpp"
#include <iostream>

struct impl
{
  int a;
};

void _init_udf(impl& pimpl, int a)
{
  std::cout << "Hello from dynamically loaded object" << std::endl;
  std::cout << "internal data: " << pimpl.a << std::endl;
}

void _make_udf(Model& model)
{
  model.pimpl = new impl;
  model.pimpl->a = 11272024;
}

// This macro can be used for trivial destruction
// This declare _delete_udf function
DECLARE_DELETER(impl)

// Don't forget to export the module (and deleter).
EXPORT_MODULE_WITH_TAG(module, 1, &_init_udf, &_make_udf, &_delete_udf);
