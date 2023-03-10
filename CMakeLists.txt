cmake_minimum_required (VERSION 3.13)

project ("zipshell")

add_subdirectory("czip")
add_library(${PROJECT_NAME} STATIC "src/zip.cpp" "src/zip.hpp" )
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/czip/src")
target_link_libraries(${PROJECT_NAME} PRIVATE zip)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
