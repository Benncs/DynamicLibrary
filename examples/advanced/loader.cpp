#include "modules/modules.hpp"
#include <cstdio>
#include <dynlib/dynlib.hpp>
#include <loader.hpp>
namespace UnsafeUDF
{
  [[nodiscard]] std::shared_ptr<DynamicLibrary> init_lib(std::string_view path)
  {
    auto _handle = DynamicLibrary::getLib(path);
    const auto _mod =
        DynamicLibrary::getModule<const Module>(_handle, &default_module);
    std::printf("build tag: %lld\r\n", _mod.build_tag);
    make_udf = _mod._make_udf_m;
    init_udf = _mod._init_udf_m;
    delete_udf = _mod._delete_udf_m;
    return _handle;
  }
} // namespace UnsafeUDF
