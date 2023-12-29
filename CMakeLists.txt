cmake_minimum_required(VERSION 3.4)
project(SakoEngine VERSION 0.0.1)

message("Setting up Generator")

if (WIN32)
  set(CMAKE_GENERATOR "MinGW Makefiles")
  message("generator is set to ${CMAKE_GENERATOR}")
elseif (LINUX)
  set(CMAKE_GENERATOR "Unix Makefiles")
  message("generator is set to ${CMAKE_GENERATOR}")
  message("theres no way anybody actually uses clang right?")
  message("wonder if it would work with crosscompiling")
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  message([FATAL_ERROR] "building on macos isnt supported yet")
endif()

# CXX standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

# cause we need the dll and stuff :D
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# support clangd language server
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (WIN32)
  message("we need to define the module path on windows for some reason.")
  set(CMAKE_MODULE_PATH "C:/Program Files/CMake/share/cmake-3.26/Modules")
else()
  message("using default Module path")
endif()

# thing
# add_custom_target(
#     copy-compile-commands ALL
#     ${CMAKE_COMMAND} -E copy_if_different
#         ${CMAKE_BINARY_DIR}/compile_commands.json
#         ${CMAKE_CURRENT_LIST_DIR}
#     )

# libraries
add_subdirectory(lib/)
# engine
add_subdirectory(Engine/)
