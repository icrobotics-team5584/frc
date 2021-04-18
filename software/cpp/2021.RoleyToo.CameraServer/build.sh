#!/bin/bash

echo "ICRobotics Web Camera Streaming System"
echo "     Build Script: 2021.RoleyToo      "
echo "  https://github.com/mitchellblaser/  "
echo ""

echo "Checking Dependencies."
sudo apt install gcc g++ cmake libjpeg8-dev -y > /dev/null
echo "Creating Build Directory."
mkdir build
echo "Building Application."
cd mjpg-streamer-experimental
mkdir build
cd build
echo "Running CMake."
cmake ..
echo "Building Binaries."
make
echo "Copying Selected Binaries."
cp plugins/input_uvc/input_uvc.so ../../build/
cp plugins/input_file/input_file.so ../../build/
cp plugins/output_http/output_http.so ../../build/
cp ./mjpg_streamer ../../build/
cp ../../www ../../build/ -r
cp ../../.test.sh ../../build/test.sh
cp ../../.start.sh ../../build/start.sh