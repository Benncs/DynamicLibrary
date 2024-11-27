#ifndef __MYMODULE_HPP__
#define __MYMODULE_HPP__
#include <dynlib/dyn_module.hpp>

struct impl;
struct Model;

namespace UsafeUDF {
static void (*make_udf)(Model &) = nullptr;
static void (*init_udf)(impl &, int) = nullptr;
static void (*delete_udf)(impl **) = nullptr;
} // namespace UsafeUDF

struct Model {
  Model() { UsafeUDF::make_udf(*this); }
  void init(int a) {
    if (pimpl != nullptr) {
      return UsafeUDF::init_udf(*pimpl, a);
    }
  }
  ~Model() {
    if (pimpl != nullptr) {
      UsafeUDF::delete_udf(&pimpl);
    }
  }
  impl *pimpl = nullptr;
};

using init_udf_ptr = decltype(UsafeUDF::init_udf);
using make_udf_ptr = decltype(UsafeUDF::make_udf);
using delete_udf_ptr = decltype(UsafeUDF::delete_udf);

DEFINE_MODULE(MODULE_ITEM(init_udf) MODULE_ITEM(make_udf)
                  MODULE_ITEM(delete_udf))

EXPORT_DEFAULT

#endif
