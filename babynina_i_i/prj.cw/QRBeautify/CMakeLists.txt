add_library(QRBeautify QRBeautify.cpp QRBeautify.h "qr_generator/qrcodegen.cpp" "qr_generator/qrcodegen.hpp")
add_library(QRBeautify::QRBeautify ALIAS QRBeautify)

target_include_directories(QRBeautify PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(QRBeautify PRIVATE PNGwriter::PNGwriter)

install(
    TARGETS QRBeautify)
