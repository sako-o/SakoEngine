add_executable(${CMAKE_PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE main.cpp window.cpp sakoengine.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE lib)
