set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
add_subdirectory(SDL)
add_subdirectory(SDL_image)
find_package(OpenGL REQUIRED)
find_package(Vulkan REQUIRED)
# TODO(sako) copy libGL to bin folder
# https://stackoverflow.com/questions/20746936/what-use-is-find-package-when-you-need-to-specify-cmake-module-path
# https://stackoverflow.com/questions/20833226/library-headers-and-define/20838147#20838147

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

# SDL3 Options 
set(SDL_TEST OFF)
set(SDL_TEST_LIBRARY OFF)
set(BUILD_SHARED_LIBS ON)

if (BUILD_SHARED_LIBS)
  message("Building with shared libraries!")
else()
  message("Building static libraries")
endif()

# SDL_IMAGE options
set(SDL3IMAGE_AVIF OFF)
set(SDL3IMAGE_BMP ON)
set(SDL3IMAGE_GIF ON)
set(SDL3IMAGE_JPG OFF)
set(SDL3IMAGE_JXL OFF)
set(SDL3IMAGE_LBM OFF)
set(SDL3IMAGE_PCX OFF)
set(SDL3IMAGE_PNG ON)
set(SDL3IMAGE_PNM OFF)
set(SDL3IMAGE_QOI OFF)
set(SDL3IMAGE_SVG OFF)
set(SDL3IMAGE_TGA OFF)
set(SDL3IMAGE_TIF OFF)
set(SDL3IMAGE_WEBP OFF)
set(SDL3IMAGE_XCF OFF)
set(SDL3IMAGE_XPM OFF)

add_library(vendor INTERFACE)
target_link_libraries(vendor INTERFACE 
  SDL3::SDL3 
  SDL3_image::SDL3_image 
  OpenGL
  OpenGL::EGL
  Vulkan
) 
