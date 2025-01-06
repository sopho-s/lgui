cmake_minimum_required(VERSION 3.10)

# Set the project name
project(lgui)

# Add an executable
add_executable(lgui main.cpp)

find_package(X11 REQUIRED)
link_libraries(${X11_LIBRARIES})
include_directories(${X11_INCLUDE_DIR})

add_subdirectory(util)

add_subdirectory(window)

target_link_libraries(lgui PRIVATE util window)