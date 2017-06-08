add_executable( simple_example "simple_example/main.c" "simple_example/my_simple_wrapper.cpp" )
target_link_libraries( simple_example wrapper )

include_directories("${GRIDTOOLS_DIR}/include")

add_executable( dycore_example "dycore_example/main.c" "dycore_example/Dycore.cpp" )
target_link_libraries( dycore_example wrapper )

add_library( dycore_library "dycore_example/Dycore.cpp" )

add_executable( dycore_example_fortran "dycore_example/main.f90" )
target_link_libraries( dycore_example_fortran wrapper )

# whole archive needed as otherwise the static initializiation won't happen
target_link_libraries( dycore_example_fortran -Wl,--whole-archive dycore_library -Wl,--no-whole-archive )
