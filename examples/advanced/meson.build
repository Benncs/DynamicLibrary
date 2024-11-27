library(
  'wrong',
  'modules/wrong.cpp',
  dependencies: dynlib_dep,
  pic: true,
  gnu_symbol_visibility: 'hidden',
  cpp_args: ['-DDEFAULT_MODULE'],
)

library(
  'external',
  'modules/external_module.cpp',
  dependencies: dynlib_dep,
  pic: true,
  gnu_symbol_visibility: 'hidden',
  cpp_args: ['-DDEFAULT_MODULE'],
)

default = library(
  'default',
  'modules/default_lib.cpp',
  dependencies: dynlib_dep,
  pic: true,
  gnu_symbol_visibility: 'hidden',
  cpp_args: ['-DDEFAULT_MODULE'],
)

executable(
  'example',
  'main.cpp',
  'loader.cpp',
  link_with: default,
  dependencies: dynlib_dep,
  cpp_args: ['-DDEFAULT_MODULE'],
)
