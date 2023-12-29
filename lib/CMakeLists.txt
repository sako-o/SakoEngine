add_subdirectory(SDL)

add_library(lib INTERFACE)
target_link_libraries(lib INTERFACE SDL3::SDL3) 

# SDL3 X11 is broken now
set_option(SDL_X11 OFF)
