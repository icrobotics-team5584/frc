#!/bin/bash

echo ---------------------------------------------------------------------------
echo INFO: purging derived objects
rm -rf ./mjpg-streamer-experimental/build

echo ---------------------------------------------------------------------------
echo INFO: constructing build environment
mkdir mjpg-streamer-experimental/build
cd mjpg-streamer-experimental/build
cmake -DPLUGIN_INPUT_OPENCV=OFF

echo ---------------------------------------------------------------------------
echo INFO: starting build
make

echo ---------------------------------------------------------------------------
echo INFO: exiting build environment
cd ../..

echo ---------------------------------------------------------------------------
echo INFO: copying in libraries not on library path
cp plugins/input_uvc/input_uvc.so .
cp plugins/output_http/output_http.so .

