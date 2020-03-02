
# Header files:

install_headers('graph.hpp')
install_headers('adjacency_list.hpp')
install_headers('adjacency_matrix.hpp')
install_headers('compressed_sparse_rows.hpp')

# Source files:

graph_utils_sources = ['utils.cpp']
graph_utils_lib = shared_library('graph_utils',
                        graph_utils_sources,
                        include_directories : inc,
#                        dependencies : glib_dep,
                        install : true)