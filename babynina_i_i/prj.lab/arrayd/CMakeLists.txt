<<<<<<< HEAD
#cmake_minimum_required(VERSION 3.24)

add_library(arrayd src/arrayd.cpp include/arrayd/arrayd.hpp)

=======
add_library(arrayd src/arrayd.cpp include/arrayd/arrayd.hpp)
set_property(TARGET arrayd PROPERTY CXX_STANDARD 20)
>>>>>>> b990f82814904657c5f3aa6783f50774377d5fd4
target_include_directories(arrayd PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
<<<<<<< HEAD
install(TARGETS arrayd)

set(CMAKE_CXX_STANDARD 20)

=======
install(TARGETS arrayd)
>>>>>>> b990f82814904657c5f3aa6783f50774377d5fd4
