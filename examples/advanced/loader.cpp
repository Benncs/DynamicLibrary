#include "loader.hpp"
#include "modules/modules.hpp"
#include <dynlib/dynlib.hpp>

namespace UnsafeUDF {
[[nodiscard]] std::shared_ptr<DynamicLibrary> init_lib(std::string_view path) {
  auto _handle = DynamicLibrary::getLib(path);
  auto _mod = DynamicLibrary::getModule<Module>(_handle);

  make_udf = _mod._make_udf_m;
  init_udf = _mod._init_udf_m;
  delete_udf = _mod._delete_udf_m;
  return _handle;
}
} // namespace UnsafeUDF
