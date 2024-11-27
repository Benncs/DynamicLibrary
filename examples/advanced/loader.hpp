#ifndef LOADER_HPP
#define LOADER_HPP
#include <string_view>
#include <memory>

#include <dynlib/dynlib.hpp>

namespace UnsafeUDF {
    [[nodiscard]] std::shared_ptr<DynamicLibrary> init_lib(std::string_view path);
}

#endif
