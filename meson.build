project(
  'dynamic-library',
  'cpp',
  version: '1.0',
  default_options: ['warning_level=3', 'cpp_std=gnu++20'],
)

shared_include = include_directories('../public')

dynlib_dep = declare_dependency(include_directories: shared_include)

subdir('examples')
