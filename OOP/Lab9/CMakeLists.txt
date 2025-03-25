cmake_minimum_required(VERSION 3.10.0)
project(lab9 VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

add_compile_options(--std=c++17)

add_executable(lab9 main.cpp task.cpp)

include(CTest)
enable_testing()

