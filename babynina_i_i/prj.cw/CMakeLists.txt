cmake_minimum_required(VERSION 3.10)

project(QRBeautifyTest)

set(CMAKE_VERBOSE_MAKEFILE True)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True) 

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin.dbg)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin.rel)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_SOURCE_DIR}/bin.relwithdbg)

find_package(PNGwriter CONFIG REQUIRED)

add_subdirectory(QRBeautify)
add_subdirectory(argParser)

add_executable(QRBeautify_Test console.cpp)
target_link_libraries(QRBeautify_Test PUBLIC argParser::argParser)

target_link_libraries(QRBeautify_Test PUBLIC QRBeautify PRIVATE PNGwriter::PNGwriter)


install(TARGETS QRBeautify_Test DESTINATION bin/bin.rel)
install(FILES cat.png examples/ex1.png examples/ex2.png examples/ex3.png DESTINATION bin/bin.rel)

add_custom_target(install_${PROJECT_NAME}
        ${CMAKE_COMMAND} -DCMAKE_INSTALL_CONFIG_NAME=${CMAKE_BUILD_TYPE}
        -P cmake_install.cmake
        )

install(DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}
        DESTINATION bin/
        FILES_MATCHING 
        PATTERN "*.dll"
        PATTERN "*.so")

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