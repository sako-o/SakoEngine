set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
add_subdirectory(SDL)
add_subdirectory(SDL_image)
find_package(OpenGL REQUIRED)
# TODO(sako) copy libGL to bin folder
# https://stackoverflow.com/questions/20746936/what-use-is-find-package-when-you-need-to-specify-cmake-module-path
# https://stackoverflow.com/questions/20833226/library-headers-and-define/20838147#20838147

# SDL3 Options 
set(SDL_TEST OFF)
set(BUILD_SHARED_LIBS ON)

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
include_directories("${OPENGL_INCLUDE_DIR}")
target_link_libraries(vendor INTERFACE SDL3::SDL3 SDL3_image::SDL3_image ${OPENGL_LIBRARY}) 

