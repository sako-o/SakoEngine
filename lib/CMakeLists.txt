find_package(OpenGL REQUIRED)
find_package(Vulkan REQUIRED)

if (OPENGL_FOUND)
  message("OpenGL Found!")
else()
  message("WARNING! OpenGL is Missing! Please install libGL")
endif()

if (VULKAN_FOUND)
  message("Vulkan Found!")
else()
  message("WARNING! Vulkan is Missing! Install the Vulkan library for linux/android support!")
endif()

add_library(vendor INTERFACE)
target_link_libraries(vendor INTERFACE 
  OpenGL
  OpenGL::EGL
  Vulkan::Vulkan
) 
