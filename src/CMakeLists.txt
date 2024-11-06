add_executable(${PROJECT_NAME} main.cpp)

file(COPY wires.bmp DESTINATION ${CMAKE_BINARY_DIR})

add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/wires.bmp ${CMAKE_CURRENT_BINARY_DIR}/wires.bmp
)
add_dependencies(${PROJECT_NAME} copy_assets)

target_link_libraries(${PROJECT_NAME} PRIVATE third_party)
