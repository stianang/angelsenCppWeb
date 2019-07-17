cmake_minimum_required(VERSION 3.10)

project(AngelsenSoftwareSystems)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create the executable
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/ControllerIndex.cpp
    src/ControllerContact.cpp
    src/ControllerBlogPost.cpp
    src/Config.cpp
    )

target_include_directories(AngelsenSoftwareSystems
    PRIVATE ${PROJECT_SOURCE_DIR}/src
)

# Link the static library from subproject1 using it's alias sub::lib1
# Link the header only library from subproject2 using it's alias sub::lib2
# This will cause the include directories for that target to be added to this project
target_link_libraries(${PROJECT_NAME}
    sub::easyweb
    sub::httputils
    sub::jinja
)
