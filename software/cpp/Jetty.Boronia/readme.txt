README.TXT
==========

PREPARATION
-----------

Unzip to a project folder e.g. /home/ubuntu/ic_pipeline

If necessary, use GRIP to generate new GripPipeline.h and GripPipeline.cpp.

If GripPipeline has nmore than parameter changes then you will need to mofify ic_pipeline.cpp to handle the changes.

Install cmake utils if ththey are not already in place ...

  sudo apt-get install cmake



BUILD STEPS
-----------

Build as follows ...

  cd /home/ubuntu/ic_pipeline
  mkdir build
  cd build
  cmake ..
  make

Clean as follows ...

  cd /home/ubuntu/ic_pipeline
  rm -rf build/*



EXECUTION STEPS
---------------

Run as follows ...

  cd /home/ubuntu/ic_pipeline
  cd build
  ./ic_pipeline



STOP EXECUTION STEPS
--------------------

You need to avoid using CTRL+C to terminate OpenCV programs (see note below).

We have implemented control file detection so that you can exit the program gracefully if needed ...

  touch /home/ubuntu/ic_pipeline/build/ic_pipeline.stop



TO SET CAMERA EXPOSURE
----------------------

CREDIT: http://www.techytalk.info/webcam-settings-control-ubuntu-fedora-linux-operating-system-cli/

To install required utils ...

  sudo apt-get install v4l-utils

To report on current status of cameras ...

  v4l2-ctl --info
  v4l2-ctl --list-ctrls
  v4l2-ctl --list-ctrls-menus
  v4l2-ctl --list-devices

Run the following command sequence to wind down exposure on /dev/video0 ...

  v4l2-ctl --set-ctrl exposure_auto=1
  v4l2-ctl --set-ctrl exposure_absolute=5

Use --device=/dev/videoX to apply to alternate device.



FIXES REQUIRED TO GENERATED CODE FROM GRIP 1.5.1
------------------------------------------------

These fixes were required to get the code building!

(a) add the following line to GripPipeline.h after "private:" ...

      cv::Mat source0;

(b) add the following line to GripPipeline.h after "GripPipeline();" ...

      void setsource0(cv::Mat& source0);

(c) edit line in GripPipeline.cpp from ...

      BlurType blurType = BlurType::GAUSSIAN;

    to ...

      BlurType blurType = GAUSSIAN;

(d) edit line in GripPipeline.cpp from ...

      double ratio = bb.width / bb.height;

    to ...

      double ratio = (double) bb.width / bb.height;

(e) Add line to end of CMakeLists.txt ...

      add_definitions(-std=c++11)

(f) Add GripPipeline.cpp file to existing add_executable() line in CMakeLists.txt ...

      add_executable(cv_ic ic.cpp GripPipeline.cpp)



FINAL CMakeLists.txt SHOULD LOOK LIKE:
-------------------------------------

  cmake_minimum_required (VERSION 2.8)
  project(ic_pipeline)
  find_package(OpenCV REQUIRED)
  include_directories(${OpenCV_INCLUDE_DIRS})
  add_executable(ic_pipeline ic_pipeline.cpp GripPipeline.cpp)
  target_link_libraries(ic_pipeline ${OpenCV_LIBS})
  add_definitions(-std=c++11)



USING CTRL+C TO TERMINATE PROGRAM
---------------------------------

This can cause "VIDIOC_STREAMON: Invalid argument" errors to be reported. This is a known problem ...

  https://lawlorcode.wordpress.com/2014/04/08/opencv-fix-for-v4l-vidioc_s_crop-error/a

... and why we use the spacebar (in debug mode) and/or control file to terminate the program gracefully.

Note that the only way to recover once you start seeing "VIDIOC_STREAMON: Invalid argument" seems to be to restart the platform ...

  sudo shutdown -r now



INTEGRATING NETWORK TABLES CODE
-------------------------------

Download network_tables.zip from Tom Bottiglieri dropbox (see https://www.dropbox.com/s/8sz4synzktl87pe/network_tables.zip?dl=0).

Unzip to /home/ubuntu/9-ic-pipeline/network_tables/.

Check path to libntcore.so ...

  ls -al /home/ubuntu/9-ic-pipeline/network_tables/network_tables/Linux/arm/libntcore.so

Edit CMakeLists.txt, it will need to look like this ...

  cmake_minimum_required (VERSION 2.8)
  project(ic_pipeline)
  find_package(OpenCV REQUIRED)
  include_directories(${OpenCV_INCLUDE_DIRS} network_tables/network_tables/include )
  add_executable(ic_pipeline ic_pipeline.cpp GripPipeline.cpp)
  target_link_libraries(ic_pipeline ${OpenCV_LIBS} /home/ubuntu/9-ic-pipeline/network_tables/network_tables/Linux/arm/libntcore.so)
  add_definitions(-Wall -std=c++11 -lstdc++ -lntcore -pthread)

And regenerate all derived objects in the normal way ...

  cd /home/ubuntu/ic_pipeline
  rm -rf build/*
  cd build
  cmake ..
  make

