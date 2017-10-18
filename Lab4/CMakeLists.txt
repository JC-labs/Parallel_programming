cmake_minimum_required(VERSION 2.6)
project (Lab)
set(CMAKE_BUILD_TYPE Release)
add_executable(Lab4 Lab4.cpp)

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/../cpp_math/include)
find_library(LibraryFound Math ${CMAKE_CURRENT_SOURCE_DIR}/../cpp_math/lib)
target_link_libraries(Lab4 ${LibraryFound})

install (TARGETS Lab4 DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)
