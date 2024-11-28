#ifndef __DYN_MODULE_HPP__
#define __DYN_MODULE_HPP__

// Template alias for function pointers.
template <typename Func> using FuncPtr = Func *;

// Macro to define a type alias for a function pointer.
#define USING_TYPE(func) using func##_ptr = FuncPtr<decltype(func)>;

#define DECLARE_DELETER(__typename__)                                          \
  void _delete_udf(__typename__ **pimpl) {                                     \
    if (pimpl != nullptr) {                                                    \
      delete *pimpl; /*NOLINT*/                                                \
      *pimpl = nullptr;                                                        \
    }                                                                          \
  }
#define _EXPOSE_CST_SYMBOL_FROM_SO                                             \
  extern const __attribute__((visibility("default")))

#define EXPORT_MODULE(__name__, ...)                                           \
  _EXPOSE_CST_SYMBOL_FROM_SO Module __name__ = {__VA_ARGS__}

// Macro to define a pointer to a module item (function or variable).
#define MODULE_ITEM(name) name##_ptr _##name##_m = nullptr;

#ifdef DEFAULT_MODULE
#define EXPORT_DEFAULT _EXPOSE_CST_SYMBOL_FROM_SO Module default_module;
#else
#define EXPORT_DEFAULT
#endif

#define DECLARE_MODULE(__name__) _EXPOSE_CST_SYMBOL_FROM_SO Module __name__

// Macro to define a module structure containing provided items.
#define DEFINE_MODULE(...)                                                     \
  typedef struct Module {                                                      \
    __VA_ARGS__                                                                \
  } *ImportedModule;

#endif
