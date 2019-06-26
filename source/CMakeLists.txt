cmake_minimum_required(VERSION 3.0)

project(micro)

enable_testing()

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_EXE_LINKER_FLAGS "-static")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_subdirectory(lib)
add_subdirectory(service/front)
