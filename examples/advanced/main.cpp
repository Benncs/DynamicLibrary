#include "modules/modules.hpp"
#include <dynlib/dynlib.hpp>
#include <exception>
#include <stdexcept>
#include <string_view>
#include "loader.hpp"

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
