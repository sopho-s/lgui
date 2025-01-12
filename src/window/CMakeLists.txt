add_library(window window.h window.cpp)

target_link_libraries(window PRIVATE util drawables objects)