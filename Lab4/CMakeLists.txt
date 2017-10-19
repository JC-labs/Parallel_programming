cmake_minimum_required(VERSION 2.6)
project (Lab)
set(CMAKE_BUILD_TYPE Release)
add_executable(Lab4 Lab4.cpp)

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/../cpp_math)
find_library(MathLib Math ${CMAKE_CURRENT_SOURCE_DIR}/../cpp_math)
find_package (Threads)
target_link_libraries(Lab4 ${MathLib} ${CMAKE_THREAD_LIBS_INIT})
