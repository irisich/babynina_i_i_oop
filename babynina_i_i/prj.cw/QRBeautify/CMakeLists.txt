cmake_minimum_required(VERSION 3.10)

project(QRBeautify)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
find_package(PNGwriter CONFIG REQUIRED)

add_library(QRBeautify QRBeautify.cpp QRBeautify.h "qr_generator/qrcodegen.cpp" "qr_generator/qrcodegen.hpp")
add_library(QRBeautify::QRBeautify ALIAS QRBeautify)

target_include_directories(QRBeautify PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(QRBeautify PRIVATE PNGwriter::PNGwriter)

install(
    TARGETS QRBeautify
    DESTINATION lib
)
