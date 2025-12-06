cmake_minimum_required(VERSION 3.28)
project(imgv LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_COMPILER "clang++")

find_package(SFML REQUIRED COMPONENTS
    Graphics
    Window
    System
    CONFIG
)

add_executable(imgv src/main.cpp)
target_compile_features(imgv PRIVATE cxx_std_23)

target_link_libraries(imgv PRIVATE SFML::Window)
target_link_libraries(imgv PRIVATE SFML::Graphics)
target_link_libraries(imgv PRIVATE SFML::System)
