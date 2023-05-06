cmake_minimum_required(VERSION 3.10)
project(SakoEngine VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_OBJCXX_STANDARD_REQUIRED ON)

message(NOTICE "


    >>>>>>>>>>> >>>>>>>>>>>>>>>>>
    >>>>>>>>>>  >>>>>>>>>>>>>>>>>
    >>>>>>>>>>  >>>>>>>>>>>>>>>>>
    >>>>>>>>    >>>>>>>>>>>>>

    >                       >
      >>>>>>>>>>>>>>>>>>>>> 

          SakoEngine




")

message(NOTICE "Building Version " ${PROJECT_VERSION})

set(CMAKE_MODULE_PATH "C:/Program Files/CMake/share/cmake-3.26/Modules")

# modules (its called vendor in the CMakelists.txt of ./lib)
# TODO:: Change library name
add_subdirectory(lib)

add_subdirectory(Engine/)
