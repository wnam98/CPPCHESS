cmake_minimum_required(VERSION 3.16)
project(CPPChess)

set(CMAKE_CXX_STANDARD 14)

## In most cases better set in the CMake cache
set(SFML_DIR "C:/Program Files (x86)/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
add_executable(CPPChess main.cpp)
target_link_libraries(CPPChess sfml-graphics sfml-audio)