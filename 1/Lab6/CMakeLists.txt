cmake_minimum_required(VERSION 3.0.2)
project (Lab)
set(CMAKE_BUILD_TYPE Release)
add_executable(Lab6 Lab6.cpp)

find_package(MPI)
find_library(MathLib Math SHARED ${CMAKE_CURRENT_SOURCE_DIR}/../cpp_math/)

IF(MPI_CXX_FOUND)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MPI_CXX_FLAGS}")
    include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../cpp_math" "${MPI_CXX_INCLUDE_PATH}")
    target_link_libraries(Lab6 "${MPI_CXX_LIBRARIES}" "${MathLib}")
    set_target_properties(Lab6 PROPERTIES COMPILE_FLAGS "${MPI_COMPILE_FLAGS}")
    set_target_properties(Lab6 PROPERTIES LINK_FLAGS "${MPI_LINK_FLAGS}")
else()
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../cpp_math)
    target_link_libraries(Lab6 ${MathLib})
ENDIF()
