project('SakoEngine', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3'])

library_path = []
project_sources = []
project_header_files = []
project_test_sources = []
project_benchmark_sources = []

inc = [include_directories('src/include')]


sakoengine_deps = [
  dependency('sdl3')
]

# sakoengine_dep_libs = [
#   foo_lib,
#   bar_lib,
#   baz_lib,
# ]


subdir('src')

SakoEngine = executable('SakoEngine',
                        main_source,
                        include_directories: inc,
                        # dependencies : sakoengine_deps,
                        # link_with : sakoengine_dep_libs
                       )
