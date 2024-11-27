#include "modules/modules.hpp"
#include <dynlib/dynlib.hpp>
#include <exception>
#include <stdexcept>
#include <string_view>

namespace UsafeUDF {
[[nodiscard]] auto init_lib(std::string_view path) {
  auto _handle = DynamicLibrary::getLib(path);
  Module _mod = DynamicLibrary::getModule<Module>(_handle);
  make_udf = _mod._make_udf_m;
  init_udf = _mod._init_udf_m;
  delete_udf = _mod._delete_udf_m;
  return _handle;
}

} // namespace UsafeUDF

#define LOAD_LIB(name) auto _ = UsafeUDF::init_lib(name);

int exec() {

  Model m;

  m.init(42);
  return 0;
}

int main(int argc, char **argv) {
  std::string_view arg0;

  if (argc == 2) {
    arg0 = argv[1];
    try {

      LOAD_LIB(arg0);
      return exec();
    } catch (...) {
      std::cerr
          << "Not default provided and library is not available: early return "
          << std::endl;
    }
  }
  return -1;
}
