find_package(glfw3 REQUIRED)

# Path to glad directory
set(GLAD_SOURCES_DIR "${PROJECT_SOURCE_DIR}/thirdparty/glad/")
# Path to glad cmake files
add_subdirectory("${GLAD_SOURCES_DIR}/cmake" glad_cmake)

# Specify glad settings
glad_add_library(glad_gl_core REPRODUCIBLE API gl:core=4.6)

add_library(third_party INTERFACE)
target_link_libraries(third_party INTERFACE glfw glad_gl_core)
