cmake_minimum_required(VERSION 3.16.3)

project(example1)



file(GLOB SRC_FILES src/*.cpp)

include_directories(
    "/usr/include/eigen-3.4.0/"
    "${CMAKE_SOURCE_DIR}/include/"
    )



add_compile_options(-O3)

set(CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)

add_executable(main ${SRC_FILES})