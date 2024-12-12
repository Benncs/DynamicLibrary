project(
  'dynamic-library',
  'cpp',
  version: '1.0',
  default_options: ['warning_level=3', 'cpp_std=gnu++20'],
)
compiler = meson.get_compiler('cpp')
shared_include = include_directories('./public')
dl_dep = compiler.find_library('dl', required : false)

dynlib_dep = declare_dependency(dependencies:dl_dep,include_directories: shared_include)

if get_option('build_examples')
subdir('examples')
endif
