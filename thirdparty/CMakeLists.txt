find_package(SDL3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

add_library(third_party INTERFACE)
target_link_libraries(third_party INTERFACE GLEW::GLEW glm::glm SDL3::SDL3)
