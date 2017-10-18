cmake_minimum_required(VERSION 2.6)
project (Math)
set(CMAKE_BUILD_TYPE Release)
add_library(Math STATIC Math.cpp)
set_target_properties(Math PROPERTIES OUTPUT_NAME Math)

install (FILES Math.hpp Matrix.hpp Vector.hpp 
	 DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include)

install (TARGETS Math DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/lib
	 PUBLIC_HEADER DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include)
