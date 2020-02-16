cmake_minimum_required (VERSION 2.8)

project(ic_pipeline)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS} /home/ubuntu/allwpilib.20200121.1500/ntcore/src/main/native/include/ /home/ubuntu/allwpilib.20200121.1500/wpiutil/src/main/native/include/)

add_executable(ic_pipeline ic_pipeline.cpp GripPipeline.cpp MJPEGWriter.cpp)

target_link_libraries(ic_pipeline ${OpenCV_LIBS} /home/ubuntu/allwpilib.20200121.1500/build/lib/libntcore.so /usr/lib/aarch64-linux-gnu/libpthread.so)

add_definitions(-Wall -std=c++17 -lstdc++ -lntcore -lopencv_highgui -lopencv_core -lpthread)

