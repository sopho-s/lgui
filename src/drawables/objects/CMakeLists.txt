add_library(objects objects.h objects.cpp bounds.cpp bounds.h)

add_subdirectory(animations)

target_link_libraries(objects PUBLIC drawables util animations)