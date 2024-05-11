find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)

add_library(third_party INTERFACE)
target_link_libraries(third_party INTERFACE Vulkan::Vulkan glfw)
