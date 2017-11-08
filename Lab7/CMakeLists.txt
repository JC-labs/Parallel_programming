cmake_minimum_required(VERSION 3.0.2)
project (Lab)
set(CMAKE_BUILD_TYPE Release)
add_executable(Lab7 Lab7.cpp)

find_library(MathLib Math SHARED ${CMAKE_CURRENT_SOURCE_DIR}/../cpp_math/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../cpp_math)
target_link_libraries(Lab7 ${MathLib})