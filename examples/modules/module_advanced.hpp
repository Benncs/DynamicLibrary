#ifndef __MODULE_2_HPP__
#define __MODULE_2_HPP__

#include <dynlib/dyn_module.hpp>

struct impl;
struct Model;

namespace UsafeUDF {
extern void (*make_udf)(Model &);
extern void (*init_udf)(impl &, int);
extern void (*delete_udf)(impl **);
} // namespace UsafeUDF

struct Model {
  Model();
  void init(int a);
  ~Model();

  impl *pimpl = nullptr;
};

using init_udf_ptr = decltype(UsafeUDF::init_udf);
using make_udf_ptr = decltype(UsafeUDF::make_udf);
using delete_udf_ptr = decltype(UsafeUDF::delete_udf);

DEFINE_MODULE(MODULE_ITEM(init_udf) MODULE_ITEM(make_udf)
                  MODULE_ITEM(delete_udf))

#endif
