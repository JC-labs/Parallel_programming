cmake_minimum_required(VERSION 2.6)
project (pp_math_lib)
add_library(Math Math.cpp)

install (TARGETS Math DESTINATION bin)
install (FILES Math.hpp DESTINATION include)
