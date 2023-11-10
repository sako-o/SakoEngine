add_subdirectory(SDL)

add_library(lib INTERFACE)
target_link_libraries(lib INTERFACE SDL3::SDL3) 
