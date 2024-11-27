#ifndef __MYMODULE_HPP__
#define __MYMODULE_HPP__

#include <dynlib/dyn_module.hpp>

using foo_ptr = int (*)(int, int);
using bar_ptr = int (*)(int);


DEFINE_MODULE(
  MODULE_ITEM(foo)
  MODULE_ITEM(bar)
)

EXPORT_DEFAULT 

#endif
