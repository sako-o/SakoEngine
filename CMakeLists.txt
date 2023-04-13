cmake_minimum_required(VERSION 3.10)

project(SakoEngine)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "path")

set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules
)

add_subdirectory(Engine/)
