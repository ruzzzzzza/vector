cmake_minimum_required(VERSION 3.24)
project(vector)

set(CMAKE_CXX_STANDARD 20)

find_package(Catch2 3 REQUIRED)

add_executable(vector test/test.cpp src/vector.cpp)
target_link_libraries(vector PRIVATE Catch2::Catch2WithMain)