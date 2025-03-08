add_library(drawables drawables.cpp drawables.h)

target_link_libraries(drawables PUBLIC glad)

add_subdirectory(objects)