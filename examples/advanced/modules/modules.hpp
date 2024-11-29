#ifndef __MYMODULE_HPP__
#define __MYMODULE_HPP__
#include <dynlib/dyn_module.hpp>

struct impl;
struct Model;

namespace UnsafeUDF {
extern void (*make_udf)(Model &);
extern void (*init_udf)(impl &, int);
extern void (*delete_udf)(impl **);
} // namespace UsafeUDF

struct Model {
  Model() ;
  void init(int a);
  ~Model() ;
  impl *pimpl = nullptr;
};

using init_udf_ptr = decltype(UnsafeUDF::init_udf);
using make_udf_ptr = decltype(UnsafeUDF::make_udf);
using delete_udf_ptr = decltype(UnsafeUDF::delete_udf);

DEFINE_MODULE(MODULE_ITEM(init_udf) MODULE_ITEM(make_udf)
                  MODULE_ITEM(delete_udf))

EXPORT_DEFAULT


#endif
