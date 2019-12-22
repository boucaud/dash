add_subdirectory(builtins)

get_directory_property(builtin_sources DIRECTORY builtins DEFINITION sources)

set(sources
${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
${CMAKE_CURRENT_SOURCE_DIR}/BuiltinCaller.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Environment.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Variable.cpp
)
