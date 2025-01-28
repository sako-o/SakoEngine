find_package(SDL3 REQUIRED)
# find_package(GLEW REQUIRED)
# find_package(glm REQUIRED)
# find_package(OpenGL REQUIRED)
find_package(Vulkan REQUIRED)

# imgui
add_library(imgui
  ./imgui/imgui.cpp ./imgui/imgui_draw.cpp
  ./imgui/imgui_tables.cpp ./imgui/imgui_widgets.cpp
  ./imgui/backends/imgui_impl_sdl3.cpp
  # ./imgui/backends/imgui_impl_opengl3.cpp
  ./imgui/backends/imgui_impl_vulkan.cpp
  ./imgui/backends/imgui_impl_sdlrenderer3.cpp)

target_include_directories(imgui PUBLIC ${SDL3_INCLUDE_DIRS})
target_include_directories(imgui PUBLIC ./imgui ./imgui/backends/)
target_compile_definitions(imgui PUBLIC GL_GLEXT_PROTOTYPES=1)

add_library(third_party INTERFACE)
target_link_libraries(third_party INTERFACE
  # GLEW::GLEW glm::glm
  SDL3::SDL3
  Vulkan::Vulkan
  imgui)
