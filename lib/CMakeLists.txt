add_subdirectory(SDL)

# SDL3 Options 
set(BUILD_SHARED_LIBS OFF)

add_library(vendor INTERFACE)
target_link_libraries(vendor INTERFACE SDL3::SDL3)
