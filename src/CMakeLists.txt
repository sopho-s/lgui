cmake_minimum_required(VERSION 3.10)

# Set the project name
project(lgui)

# Add an executable
add_executable(lgui main.cpp)

find_package(X11 REQUIRED)
find_package(PNG REQUIRED)
find_package(glfw3 REQUIRED)
find_package(PkgConfig REQUIRED)
link_libraries(${X11_LIBRARIES})
link_libraries(PNG::PNG)
link_libraries(glfw)
include_directories(${X11_INCLUDE_DIR})

include(FetchContent)
FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG master
)
FetchContent_MakeAvailable(glad)

# Link libraries
target_link_libraries(lgui PRIVATE glad)

add_subdirectory(util)

add_subdirectory(window)

add_subdirectory(drawables)

target_link_libraries(lgui PRIVATE util window drawables objects)