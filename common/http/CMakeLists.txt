cmake_minimum_required(VERSION 3.10)

# Set the project name
project (httputils)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(Simple-Web-Server)

# Add a library with the above sources
add_library(${PROJECT_NAME} HttpUtility.cpp EmailClientSendInBlue.cpp)
add_library(sub::httputils ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}
    PRIVATE ${PROJECT_SOURCE_DIR}/Simple-Web-Server
    PRIVATE ${PROJECT_SOURCE_DIR}/asio-1.12.2/include
)

target_link_libraries(httputils simple-web-server)

