cmake_minimum_required(VERSION 3.10)

# Set the project name
project (easyweb)

# Add a library with the above sources
add_library(${PROJECT_NAME} WebFile.cpp)
add_library(sub::easyweb ALIAS ${PROJECT_NAME})

target_include_directories(easyweb
    PUBLIC ${PROJECT_SOURCE_DIR}
)
