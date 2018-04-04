cmake_minimum_required(VERSION 2.6)
project (Lab)
set(CMAKE_BUILD_TYPE Release)
add_executable(Lab4 Lab4.cpp)

find_package (Threads)
target_link_libraries(Lab4 ${CMAKE_THREAD_LIBS_INIT})