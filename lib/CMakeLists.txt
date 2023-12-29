set(SDL_TEST OFF)
# broken x11 for some reason
set(SDL_X11 OFF)
add_subdirectory(SDL)

add_library(lib INTERFACE)
target_link_libraries(lib INTERFACE SDL3::SDL3) 
