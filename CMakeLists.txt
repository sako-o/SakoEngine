cmake_minimum_required(VERSION 3.10)
project(SakoEngine VERSION 0.0.1)

message(NOTICE "


    >>>>>>>>>>> >>>>>>>>>>>>>>>>>
    >>>>>>>>>>  >>>>>>>>>>>>>>>>>
    >>>>>>>>>>  >>>>>>>>>>>>>>>>>
    >>>>>>>>    >>>>>>>>>>>>>

    >                       >
      >>>>>>>>>>>>>>>>>>>>> 

          SakoEngine




")

message(NOTICE "Building Version "${PROJECT_VERSION})

set(CMAKE_MODULE_PATH "C:/Program Files/CMake/share/cmake-3.26/Modules")

add_subdirectory(Engine/)
