cmake_minimum_required(VERSION 3.10)
project(SakoEngine VERSION 0.0.1)

# cause we need the dll and stuff :D
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_OBJCXX_STANDARD_REQUIRED ON)

# for neovim/vim clangd language server
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

message(NOTICE "Building Version " ${PROJECT_VERSION})

if (WIN32)
  message("Setting module path")
  set(CMAKE_MODULE_PATH "C:/Program Files/CMake/share/cmake-3.26/Modules")
else()
  message("Using default Module path")
endif()

# modules (its called vendor in the CMakelists.txt of ./lib)
# TODO:: Change library name
add_subdirectory(lib)

add_subdirectory(Engine/)
