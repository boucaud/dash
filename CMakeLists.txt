cmake_minimum_required(VERSION 3.10)
project(DASH VERSION 0.1)

set (SRC src/main.cpp src/Environment.cpp src/Variable.cpp src/BuiltinCaller.cpp)

add_executable(dash ${SRC})
