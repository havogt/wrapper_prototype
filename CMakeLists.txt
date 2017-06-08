cmake_minimum_required (VERSION 2.8)
project (wrapper)

include_directories( "wrapper/include" )

set( GRIDTOOLS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/gridtools" CACHE STRING "Gridtools dir")
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")

add_subdirectory( "wrapper" )
add_subdirectory( "usercode" )
