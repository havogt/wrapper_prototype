add_executable( simple_example "simple_example/main.c" "simple_example/init_simple_wrapper.cpp" "simple_example/my_simple_wrapper.cpp" )
target_link_libraries( simple_example wrapper )

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../external/gridtools/include")
add_executable( dycore_example "dycore_example/main.c" "dycore_example/dycore_init.cpp" )
target_link_libraries( dycore_example wrapper )

