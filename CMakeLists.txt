cmake_minimum_required(VERSION 3.10)
project(ADSH VERSION 0.1)

set (SRC src/main.cpp src/Environment.cpp src/Variable.cpp)

add_executable(adsh ${SRC})
