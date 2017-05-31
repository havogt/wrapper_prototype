cmake_minimum_required (VERSION 2.8)
project (wrapper)

include_directories( "wrapper/include" )

add_subdirectory( "wrapper" )
add_subdirectory( "usercode" )
