#ifndef __DYN_MODULE_HPP__
#define __DYN_MODULE_HPP__

#ifdef DEFAULT_MODULE
// If DEFAULT_MODULE is defined, EXPORT is defined as 'extern'.
#define EXPORT extern
#define EXPORT_DEFAULT EXPORT Module default_module;
#else
// If DEFAULT_MODULE is not defined, EXPORT is defined as 'extern "C"'.
#define EXPORT extern "C"
#define EXPORT_DEFAULT
#endif

// Template alias for function pointers.
template <typename Func> using FuncPtr = Func *;

// Macro to define a type alias for a function pointer.
#define USING_TYPE(func) using func##_ptr = FuncPtr<decltype(func)>;
#define EXPORT_MODULE(__name__) __attribute__((visibility("default"))) Module __name__
// Macro to define a pointer to a module item (function or variable).
#define MODULE_ITEM(name) name##_ptr _##name##_m = nullptr;

// Macro to define a module structure containing provided items.
#define DEFINE_MODULE(...) typedef struct Module {\
  __VA_ARGS__ \
} *ImportedModule;



#endif
