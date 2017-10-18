cmake_minimum_required(VERSION 2.6)
project (pp_math_lib)
add_library(math math.cpp)

install (TARGETS math DESTINATION bin)
install (FILES math.hpp DESTINATION include)