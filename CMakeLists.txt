cmake_minimum_required(VERSION 3.25)
project(untitled)

set(CMAKE_CXX_STANDARD 11)

add_executable(untitled main.cpp)

target_link_libraries(untitled -lfreeGLUT -lOpenGL32 -lglu32)