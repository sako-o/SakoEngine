# graphics libraries
find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)

# graphics math library
find_package(glm CONFIG REQUIRED)

add_library(third_party INTERFACE)
target_link_libraries(third_party INTERFACE Vulkan::Vulkan glfw glm::glm)
