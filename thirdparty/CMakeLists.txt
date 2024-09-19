find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

add_library(third_party INTERFACE)
target_link_libraries(third_party INTERFACE SDL2::SDL2 GLEW::GLEW glm::glm)
