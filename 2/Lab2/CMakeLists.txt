cmake_minimum_required(VERSION 3.8)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
project (Lab)
set(CMAKE_BUILD_TYPE Release)
add_executable(Lab2 Lab2.cpp)

find_package (Threads)
target_link_libraries(Lab2 ${CMAKE_THREAD_LIBS_INIT})

