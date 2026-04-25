cmake_minimum_required(VERSION 3.20)
project(impls)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(main ${SOURCES})
