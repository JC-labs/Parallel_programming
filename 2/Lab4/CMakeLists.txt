cmake_minimum_required(VERSION 3.8)
project (Lab)
set(CMAKE_BUILD_TYPE Release)
add_executable(Lab4 Lab4.cpp)

find_package (Threads)
target_link_libraries(Lab4 ${CMAKE_THREAD_LIBS_INIT})

OPTION (USE_OpenMP "Use OpenMP" ON)
IF(USE_OpenMP)
  FIND_PACKAGE(OpenMP)
  IF(OPENMP_FOUND)
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS} -std=c++17")
  ENDIF()
ENDIF()