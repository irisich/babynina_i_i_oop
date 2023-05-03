#cmake_minimum_required(VERSION 3.24)

add_library(arrayd src/arrayd.cpp include/arrayd/arrayd.hpp)

add_library(arrayd src/arrayd.cpp include/arrayd/arrayd.hpp)
set_property(TARGET arrayd PROPERTY CXX_STANDARD 20)
target_include_directories(arrayd PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

install(TARGETS arrayd)

set(CMAKE_CXX_STANDARD 20)
