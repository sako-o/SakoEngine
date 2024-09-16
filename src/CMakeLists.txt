add_executable(${PROJECT_NAME} main.cpp)

find_package(glfw3 REQUIRED)
target_link_libraries(${PROJECT_NAME} glfw)
