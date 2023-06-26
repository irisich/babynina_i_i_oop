cmake_minimum_required(VERSION 3.10)
project(QRBeautifyTest)

find_package(PNGwriter CONFIG REQUIRED)

add_subdirectory(QRBeautify)
add_subdirectory(argParser)

add_executable(QRBeautify_Test console.cpp)
target_link_libraries(QRBeautify_Test PUBLIC argParser::argParser)

target_link_libraries(QRBeautify_Test PUBLIC QRBeautify PRIVATE PNGwriter::PNGwriter)

target_include_directories(QRBeautify_Test PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/QRBeautify"
                          )

install(TARGETS QRBeautify_Test DESTINATION bin)

############

#add_executable(QRBeautifyTest app.cpp)

#find_package(CLI11 CONFIG REQUIRED)
#target_link_libraries(QRBeautifyTest PRIVATE CLI11::CLI11)

#target_include_directories(QRBeautifyTest PUBLIC
#                          "${PROJECT_BINARY_DIR}"
#                          "${PROJECT_SOURCE_DIR}/QRBeautify"
#                          )

#target_link_libraries(QRBeautifyTest PUBLIC QRBeautify PRIVATE PNGwriter::PNGwriter)

#install(TARGETS QRBeautifyTest DESTINATION bin)