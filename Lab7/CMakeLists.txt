cmake_minimum_required(VERSION 3.1.3)
project (Lab)
set(CMAKE_BUILD_TYPE Release)
add_executable(Lab7 Lab7.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../cpp_math)
find_library(MathLib Math SHARED ${CMAKE_CURRENT_SOURCE_DIR}/../cpp_math/)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)
target_link_libraries(Lab7 ${MathLib} Threads::Threads)