#include "modules.hpp"
#include <iostream>

struct impl {

};


static void _init_udf(impl &, int a) { std::cout << "a=" << a << std::endl; }

static void _make_udf(Model &model) { model.pimpl = new impl; }

static void _delete_udf(impl **pimpl) {
  if (pimpl != nullptr) {
    delete *pimpl;
    *pimpl = nullptr;
  }
}


#ifdef DEFAULT_MODULE
Module default_module = {&_init_udf, &_make_udf,
                         &_delete_udf};
#else
static Module module = {&init_udf, &make_udf, &delete_udf};
#endif
