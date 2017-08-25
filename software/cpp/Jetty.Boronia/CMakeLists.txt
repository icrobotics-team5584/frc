cmake_minimum_required (VERSION 2.8)

project(ic_pipeline)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(ic_pipeline ic_pipeline.cpp GripPipeline.cpp)

target_link_libraries(ic_pipeline ${OpenCV_LIBS})

add_definitions(-std=c++11)

