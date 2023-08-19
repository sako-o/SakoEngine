# Corresponding Graphics Libraries 
find_package(OpenGL REQUIRED)
find_package(Vulkan)
# TODO(sako) add DirectX
# SDL
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

if (OPENGL_FOUND)
  message("OpenGL Found!")
else()
  message("You need OpenGL to compile")
endif()

if (VULKAN_FOUND)
  message("Vulkan Found!")
else()
  message("WARNING! Vulkan is Missing! Install the Vulkan library for linux/android support!")
endif()

if (SDL2_FOUND)
  message("SDL2 Found!")
else()
  message("SDL2 Is required to build project")
endif()


if (SDL2_image_FOUND)
  message("SDL2_IMAGE Found!")
else()
  message("SDL2_Image is required")
endif()


add_library(vendor INTERFACE)
target_link_libraries(vendor INTERFACE 
  SDL2::SDL2
  SDL2_image::SDL2_image
  OpenGL
  OpenGL::EGL
  Vulkan::Vulkan
) 
