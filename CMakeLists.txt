cmake_minimum_required(VERSION 3.14)
project(cpp_verify)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")

add_subdirectory(access-specifier)
add_subdirectory(templates)
add_subdirectory(about-reference)
add_subdirectory(memory-problems)
add_subdirectory(default-functions)
add_subdirectory(rvalue-ref&stdmove)
add_subdirectory(smart-pointers)
add_subdirectory(nullptr)
add_subdirectory(auto)
add_subdirectory(4.11type-casting)
add_subdirectory(15OOP)