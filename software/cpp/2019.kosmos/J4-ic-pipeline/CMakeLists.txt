cmake_minimum_required (VERSION 2.8)

project(ic_pipeline)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS} network_tables/network_tables/include )

add_executable(ic_pipeline ic_pipeline.cpp GripPipeline.cpp)

target_link_libraries(ic_pipeline ${OpenCV_LIBS} /home/ubuntu/J4-ic-pipeline/network_tables/network_tables/Linux/arm/libntcore.so)

add_definitions(-Wall -std=c++11 -lstdc++ -lntcore -pthread)

