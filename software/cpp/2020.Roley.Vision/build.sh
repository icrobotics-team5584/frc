#!/bin/bash

echo ---------------------------------------------------------------------------
echo INFO: purging derived objects
rm -rf ./build

echo ---------------------------------------------------------------------------
echo INFO: constructing build environment
mkdir build
cd build
cmake ..

echo ---------------------------------------------------------------------------
echo INFO: starting build
make

echo ---------------------------------------------------------------------------
echo INFO: copying in libraries not on library path
cp ~/allwpilib.20200121.1500/build/lib/lib* .

echo ---------------------------------------------------------------------------
echo INFO: exiting build environment
cd ..
