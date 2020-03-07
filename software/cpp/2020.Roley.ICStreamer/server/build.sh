#!/bin/bash

echo ---------------------------------------------------------------------------
echo INFO: constructing build environment
cd mjpg-streamer-experimental
cmake -DPLUGIN_INPUT_OPENCV=OFF

echo ---------------------------------------------------------------------------
echo INFO: starting build
make

echo ---------------------------------------------------------------------------
echo INFO: copying in libraries not on library path
cp plugins/input_uvc/input_uvc.so .
cp plugins/output_http/output_http.so .

echo ---------------------------------------------------------------------------
echo INFO: exiting build environment
cd ..
