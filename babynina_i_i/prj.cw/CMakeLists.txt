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
