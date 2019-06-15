cmake_minimum_required(VERSION 3.0)

project(micro-service)

enable_testing()

set(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_subdirectory(lib)
add_subdirectory(service)
