cmake_minimum_required(VERSION 3.10)

project(SakoEngine)

if(NOT PNG AND WIN32 AND NOT MSVC)
  # booo cmake boooo
  # find_package(PNG REQUIRED)
  set(PNG_LIBRARY "C:/Program Files(x86)/libpng")
  set(PNG_LIBRARY "C:/Program Files(x86/libpng/include")
endif()

find_package(SDL2 REQUIRED)
find_package(SDL_image REQUIRED)

target_include_directories(${PROJECT_NAME} 
    PUBLIC ${SDL2_INCLUDE_DIRS}
    PUBLIC ${SDL2IMAGE_INCLUDE_DIRS}
    # PUBLIC include/
)

if(WIN32 AND NOT MSVC)
  target_link_libraries(${PROJECT_NAME} PUBLIC ${SDL2_LIBRARIES} SDL2_image::SDL2_image mingw32)
else()
  target_link_libraries(${PROJECT_NAME} PUBLIC ${SDL2_LIBRARIES} SDL2_image::SDL2_image)
endif()
