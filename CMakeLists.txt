cmake_minimum_required(VERSION 3.20)
project(Musique)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

find_package(raylib REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(MPV REQUIRED mpv)


file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(main ${SOURCES})

target_link_libraries(main PRIVATE raylib ${MPV_LIBRARIES})
target_include_directories(main PRIVATE ${MPV_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/include)
