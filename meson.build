project('fastnet', 'cpp',
  version : '1.0.0',
  license : 'MIT')
add_global_arguments('-DSOME_TOKEN=value', language : 'cpp')

# External dependencies:
gtest = subproject('gtest', version : '1.10.0')

# Actual instantiation of external dependencies:
subdir('third_party')

# Include creation:
inc = include_directories('./')

# Subdirs:
subdir('structures')

# Executables:
main_sources = ['main.cpp']
main_exec = executable('main', main_sources,
                    include_directories : inc,
#                     dependencies : glib_dep,
                    install : true,
#                    link_with: graph_utils_lib
                    )
test('main test', main_exec)
subdir('tests')