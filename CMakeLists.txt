cmake_minimum_required(VERSION 3.13)

project(oozip)

add_library(${PROJECT_NAME} src/zip.hpp src/zip.cpp)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

add_subdirectory(czip)

target_include_directories(${PROJECT_NAME} PRIVATE czip/src)
target_link_libraries(${PROJECT_NAME} PRIVATE zip)

# Testing

enable_testing()
add_subdirectory(tests)
