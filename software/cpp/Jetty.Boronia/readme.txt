README.TXT
==========



BUILD STEPS
-----------

Build as follows ...

  mkdir build
  cd build
  cmake ..
  make

Clean as follows ...

  rm -rf build/*



EXECUTION STEPS
---------------

Run as follows ...

  cd build
  ./ic_pipeline



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

(d) Add line to end of CMakeLists.txt ...
                add_definitions(-std=c++11)

(e) Add GripPipeline.cpp file to existing add_executable() line in CMakeLists.txt ...
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

