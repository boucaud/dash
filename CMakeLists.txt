cmake_minimum_required(VERSION 3.10)
project(DASH VERSION 0.1)

add_subdirectory(src)
get_directory_property(src_sources DIRECTORY src DEFINITION sources)
get_directory_property(src_builtin_sources DIRECTORY src DEFINITION builtin_sources)

add_executable(dash ${src_sources} ${builtin_sources})
