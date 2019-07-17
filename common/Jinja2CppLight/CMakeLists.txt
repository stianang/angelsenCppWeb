cmake_minimum_required(VERSION 2.8)

project(Jinja2CppLight)

add_library(${PROJECT_NAME} STATIC src/Jinja2CppLight.cpp src/stringhelper.cpp)
add_library(sub::jinja ALIAS ${PROJECT_NAME})

target_include_directories(Jinja2CppLight
    PUBLIC ${PROJECT_SOURCE_DIR}/src
)
