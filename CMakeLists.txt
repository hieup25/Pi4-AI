#Create HieuPV
#21/06/21

cmake_minimum_required(VERSION 2.8.9)
project (test)

#add lib opencv_world
set (LIB_OPENCV libopencv_world.so)
include_directories(libs/opencv/include/opencv4)
link_directories(libs/opencv/lib)

#add lib ncnn
set (LIB_NCNN libncnn.so)
include_directories(libs/ncnn/include)
link_directories(libs/ncnn/lib)

#add source
file(GLOB SOURCES "src/*.cpp")

#add include
#file(GLOB INCLUDE "src/Core/ApiSupport/*.hpp" "src/Core/Framework/ncnn/*.hpp")
#include_directories(${INCLUDE})

add_executable(test ${SOURCES})
target_link_libraries(test ${LIB_OPENCV} ${LIB_NCNN})