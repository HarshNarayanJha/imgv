cmake_minimum_required(VERSION 3.28)
project(imgv LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_COMPILER "clang++")

find_package(SFML REQUIRED COMPONENTS
    Graphics
    Window
    System
)

add_executable(imgv
    src/main.cpp
    src/parser.cpp
)

target_include_directories(imgv PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_compile_features(imgv PRIVATE cxx_std_23)

target_link_libraries(imgv PRIVATE
    SFML::Window
    SFML::Graphics
    SFML::System
)
