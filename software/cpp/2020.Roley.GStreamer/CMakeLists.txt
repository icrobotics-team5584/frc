cmake_minimum_required (VERSION 2.8)

project(ic_gstserver)

include_directories(/home/ubuntu/allwpilib.20200121.1500/ntcore/src/main/native/include/ /home/ubuntu/allwpilib.20200121.1500/wpiutil/src/main/native/include/)

add_executable(ic_gstserver ic_gstserver.cpp)

target_link_libraries(ic_gstserver /home/ubuntu/allwpilib.20200121.1500/build/lib/libntcore.so)

add_definitions(-Wall -std=c++17 -lntcore)
