/**
 * @file dynlib.hpp
 * @brief Defines the DynamicLibrary class for loading and accessing symbols
 * from dynamic libraries.
 *
 * This file provides the declaration of the DynamicLibrary class, which
 * encapsulates functionality for loading dynamic libraries and retrieving
 * symbols from them. It also includes necessary headers and type definitions
 * required for the class implementation.
 *
 * @author CASALE Benjamin
 * @date 08/03/2024
 */

#ifndef __DYNLIB_HPP__
#define __DYNLIB_HPP__

#include <iostream>
#include <memory>
#include <string_view>

#include <stdexcept>

/**
 * @brief Represents a dynamic library.
 */
class DynamicLibrary {
public:
  /**
   * @brief Retrieves an item from the dynamic library by its name.
   *
   * @tparam T The type of the item to retrieve.
   * @param fname The name of the item.
   * @return T The retrieved item.
   */
  template <typename T> T getItem(std::string_view fname);

  // Destructor
  ~DynamicLibrary() = default;

  /**
   * @brief Retrieves a dynamic library object given its path.
   *
   * @param path The path to the dynamic library.
   * @return std::shared_ptr<DynamicLibrary> A shared pointer to the dynamic
   * library object.
   */
  static std::shared_ptr<DynamicLibrary> getLib(std::string_view path) {
    try {
      auto lib = new DynamicLibrary(path);
      return std::shared_ptr<DynamicLibrary>(lib);
    } catch (std::exception &e) {
      return nullptr;
    }
  }

  /**
   * @brief Retrieves a module from the dynamic library.
   *
   * @tparam ModuleType The type of the module to retrieve.
   * @param lib_handle A shared pointer to the dynamic library.
   * @param _def Default value of the module if not found.
   * @param modulename The name of the module to retrieve.
   * @return ModuleType The retrieved module.
   */
  template <typename ModuleType>
  static ModuleType getModule(std::shared_ptr<DynamicLibrary> lib_handle,
                              ModuleType *_def = nullptr,
                              std::string_view modulename = "module");

private:
  /**
   * @brief Private constructor for DynamicLibrary.
   *
   * @param path The path to the dynamic library.
   */
  DynamicLibrary(std::string_view path) {
    this->_impl = std::make_unique<Impl>(path);
  }

  // Forward declaration of Impl class
  class Impl;

  // Pointer to the implementation object
  std::unique_ptr<Impl> _impl;
};

/// LINUX IMPLEMENTATION
#if defined(__linux__)

#include <dlfcn.h>

class DynamicLibrary::Impl {
public:
  /**
   * @brief Constructs the implementation object for the dynamic library.
   *
   * @param path The path to the dynamic library.
   */
  Impl(std::string_view path) {
    this->handle = dlopen(std::string(path).c_str(), RTLD_NOW);

    if (!handle) {
      throw std::runtime_error("Library cannot be loaded");
    }
  }

  /**
   * @brief Retrieves a function from the dynamic library by its name.
   *
   * @tparam T The type of the function to retrieve.
   * @param fname The name of the function.
   * @return T The retrieved function.
   */
  template <typename T> T getFunction(std::string_view fname) {
    void *symbol = dlsym(handle, std::string(fname).c_str());
    T f = static_cast<T>(symbol);
    return f;
  }

  // Destructor
  ~Impl() {
    if (handle) {
      dlclose(handle);
    }
    handle = nullptr;
  }

private:
  void *handle; // Handle to the dynamic library
};

#endif

#if defined(WIN32) || defined(WIN64)
#include <windows.h>

class DynamicLibrary::Impl {
public:
  /**
   * @brief Constructs the implementation object for the dynamic library.
   *
   * @param path The path to the dynamic library.
   */
  Impl(std::string_view path) {
    this->handle = LoadLibraryA(path.data());

    if (!handle) {
      throw std::runtime_error("Library cannot be loaded");
    }
  }

  /**
   * @brief Retrieves a function from the dynamic library by its name.
   *
   * @tparam T The type of the function to retrieve.
   * @param fname The name of the function.
   * @return T The retrieved function.
   */
  template <typename T> T getFunction(std::string_view fname) {
    FARPROC symbol = GetProcAddress(handle, fname.data());
    return reinterpret_cast<T>(symbol);
  }

  // Destructor
  ~Impl() {
    if (handle) {
      FreeLibrary(static_cast<HMODULE>(handle));
    }
    handle = nullptr;
  }

private:
  HMODULE handle; // Handle to the dynamic library
};
#endif

// Implementation of getModule for DynamicLibrary class
template <typename ModuleType>
ModuleType DynamicLibrary::getModule(std::shared_ptr<DynamicLibrary> lib_handle,
                                     ModuleType *_def,
                                     std::string_view modulename) {
  ModuleType _mod;
  // Check if the lib is correclty openned
  if (!lib_handle) {
    // if not
    if (!_def) {
      // If no default module is provided
      throw std::runtime_error(
          "Library is not loaded correctly and no default one is provided");
    }
    _mod = *_def; // Else we get the default instead of the
  } else {
    auto sym = lib_handle->getItem<ModuleType *>(modulename);
    if (!sym) {
      if (!_def) {
        throw std::runtime_error(
            "Cannot find required symbol and no default one is provided");
      } else {
        _mod = *_def; // IF the lib is opened but we can find the wanted symbol
                      // we use the defaul;t
        std::cerr << "Symbol not found, using default implementation"
                  << std::endl;
      }
    } else {
      _mod = *sym;
    }
  }
  return _mod;
}

// Implementation of getItem for DynamicLibrary class
template <typename T> T DynamicLibrary::getItem(std::string_view fname) {
  if (!_impl) {
    throw std::runtime_error("DynamicLibrary is not initialized properly");
  }
  return _impl->getFunction<T>(fname);
}

#endif
