README.TXT
==========

These notes describe how to set up, build and use an image pipeline that was generated using the GRIP program. The target system in this case is an Nvidia Jetson NANO development board.



PREREQUISITES
-------------

Nvidia Jetson NANO plus Microsoft HD3000 webcam.

NANO needs imaging, this is easiest achived using the Nvidia Jetpack - instructions for this task are out of scope for these notes.



PREPARATION
-----------

Unzip to a project folder e.g. /home/ubuntu/Projects/2020.Roley.Vision

If necessary, use GRIP to generate new GripPipeline.h and GripPipeline.cpp.

If GripPipeline has more than parameter changes then you will need to mofify ic_pipeline.cpp to handle the changes.

Install cmake utils if ththey are not already in place ...

  sudo apt-get install cmake



BUILD STEPS
-----------

Build as follows ...

  cd /home/ubuntu/Projects/2020.Roley.Vision
  mkdir build
  cd build
  cmake ..
  make

Clean as follows ...

  cd /home/ubuntu/Projects/2020.Roley.Vision
  rm -rf build/*



EXECUTION STEPS
---------------

Run as follows ...

  cd /home/ubuntu/Projects/2020.Roley.Vision
  cd build
  ./ic_pipeline



AUTOMATED EXECUTION ON BOOT
---------------------------

Create a script at /home/ubuntu/Projects/2020.Roley.Vision/ic_pipeline.sh

With content:

  #!/bin/bash
  # setup camera
  /usr/bin/v4l2-ctl --set-ctrl exposure_auto=1
  /usr/bin/v4l2-ctl --set-ctrl exposure_absolute=5
  # purge old log file
  /bin/rm -f /tmp/ic_pipeline.log
  # run application
  cd /home/ubuntu/Projects/2020.Roley.Vision/build
  ./ic_pipeline >> /tmp/ic_pipeline.log 2>&1

Add this line to the ubuntu user's crontab ...

  @reboot /bin/sleep 60; /home/ubuntu/Projects/2020.Roley.Vision/ic_pipeline.sh

Restart the jetson and confirm that pipeline is operational:

  - check for process running with "ps -ef | grep ic_pipeline"
  - check for log file growing with "tail -f /tmp/ic_pipeline.txt"
  - check for JETSON timestamp being updetaed in the roborio network
    table using "online viewer" on driver station or PC connected to
    the robot network



STOP EXECUTION STEPS
--------------------

You need to avoid using CTRL+C to terminate OpenCV programs (see note below).

We have implemented control file detection so that you can exit the program gracefully if needed ...

  touch /home/ubuntu/Projects/2020.Roley.Vision/build/ic_pipeline.stop

or, to terminate all running pipelines ...

  touch /tmp/ic_pipeline.stop



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

      void SetSource0(cv::Mat& source0);

(c) add the following function to GripPipeline.cpp after "void GripPipeline::Process(cv::Mat& source0)" function

      void GripPipeline::setsource0(cv::Mat &source0){
        source0.copyTo(this->source0);
      }

(d) edit line in GripPipeline.cpp from ...

      BlurType blurType = BlurType::GAUSSIAN;

    to ...

      BlurType blurType = GAUSSIAN;

(e) edit line in GripPipeline.cpp from ...

      double ratio = bb.width / bb.height;

    to ...

      double ratio = (double) bb.width / bb.height;

(f) Add line to end of CMakeLists.txt ...

      add_definitions(-std=c++17)

(g) Add GripPipeline.cpp file to existing add_executable() line in CMakeLists.txt ...

      add_executable(cv_ic ic.cpp GripPipeline.cpp)



PRIOR TO INTEGTRATING NETWORK TABLES THE CMakeLists.txt SHOULD LOOK LIKE:
-------------------------------------------------------------------------

  cmake_minimum_required (VERSION 2.8)
  project(ic_pipeline)
  find_package(OpenCV REQUIRED)
  include_directories(${OpenCV_INCLUDE_DIRS})
  add_executable(ic_pipeline ic_pipeline.cpp GripPipeline.cpp)
  target_link_libraries(ic_pipeline ${OpenCV_LIBS})
  add_definitions(-std=c++17)



USING CTRL+C TO TERMINATE PROGRAM
---------------------------------

This can cause "VIDIOC_STREAMON: Invalid argument" errors to be reported. This is a known problem ...

  https://lawlorcode.wordpress.com/2014/04/08/opencv-fix-for-v4l-vidioc_s_crop-error/a

... and why we use the spacebar (in debug mode) and/or control file to terminate the program gracefully.

Note that the only way to recover once you start seeing "VIDIOC_STREAMON: Invalid argument" seems to be to restart the platform ...

  sudo shutdown -r now



INTEGRATING NETWORK TABLES CODE
-------------------------------

Download allwpilib repo from github and checkout master, we created the clone at /home/ubuntu/allwpilib.20200221.1500 torecord the time that we took the code from github.

  cd ~/allwpilib.20200121.1500
  git checkout master
  git checkout .

Edit CMakeList.txt file ...

  cd ~/allwpilib.20200121.1500
  vi CMakeList.txt
  (change "OFF" to "ON" in the "option(WITHOUT_JAVA ..." line)

And build that code base ...

  cd ~/allwpilib.20200121.1500
  mkdir build
  cd build
  cmake ..
  make

Edit CMakeLists.txt in the ic_pieline project, it will need to look like this ...

  cmake_minimum_required (VERSION 2.8)
  project(ic_pipeline)
  find_package(OpenCV REQUIRED)
  include_directories(${OpenCV_INCLUDE_DIRS} /home/ubuntu/allwpilib.20200121.1500/ntcore/src/main/native/include/ /home/ubuntu/allwpilib.20200121.1500/wpiutil/src/main/native/include/)
  add_executable(ic_pipeline ic_pipeline.cpp GripPipeline.cpp)
  target_link_libraries(ic_pipeline ${OpenCV_LIBS} /home/ubuntu/allwpilib.20200121.1500/build/lib/libntcore.so)
  add_definitions(-Wall -std=c++17 -lstdc++ -lntcore -pthread)

And regenerate all derived objects in the ic_pipeline project in the normal way ...

  cd /home/ubuntu/Projects/2020.Roley.Vision
  rm -rf build/*
  cd build
  cmake ..
  make



BUILD OPENCV PACKAGE WITH CUDA SUPPORT
--------------------------------------

(CREDIT: https://www.jetsonhacks.com/2019/11/22/opencv-4-cuda-on-jetson-nano/)

Note that NANO Jetpack versions do ship with an OpenCV build (3.4) but this is not compiled with CUDA support so there are no GPU versions of the OpenCV libraries. Sigh.

This means we have to build our own. This is a time consuming process which is desctribed in full here. We have also copied off the resulting packages so, if we do need to construct another SD card in a hurry this should save a bit of time! 

Login as ubuntu/ubuntu then . . .

$ cd
$ git clone https://github.com/JetsonHacksNano/buildOpenCV
$ cd buildOpenCV
$ vi buildOpenCV.sh
(change NUM_JOBS to 1 as recommended in the comments)
$ ./buildOpenCV.sh |& tee openCV_build.log
(enter password for sudo access when prompted)

Build took 4 hours using SDCARD, may want to investigate USB options if we have to do this regularly.

Packages created by this process...

~/opencv/build/OpenCV-4.1.1-dirty-aarch64.sh
~/opencv/build/OpenCV-4.1.1-dirty-aarch64.tar.gz
~/opencv/build/OpenCV-4.1.1-dirty-aarch64.tar.Z

Copied off these files for safe keeping in case we need to rebuild a new SDCARD in a hurry!


INTEGRATING MJPEGWRITER CODE
----------------------------

(CREDIT: https://github.com/JPery/MJPEGWriter/blob/master/README.md)

MJPEGWriter.h and MJPEGWriter.cpp copied in from the above github project, CMakeList.txt updated to include MJPEGWriter.cpp in executable definition, required library path added plus linker library dependencies. The revised CMakeList.txt looks like:

  cmake_minimum_required (VERSION 2.8)
  project(ic_pipeline)
  find_package(OpenCV REQUIRED)
  include_directories(${OpenCV_INCLUDE_DIRS} /home/ubuntu/allwpilib.20200121.1500/ntcore/src/main/native/include/ /home/ubuntu/allwpilib.20200121.1500/wpiutil/src/main/native/include/)
  add_executable(ic_pipeline ic_pipeline.cpp GripPipeline.cpp MJPEGWriter.cpp)
  target_link_libraries(ic_pipeline ${OpenCV_LIBS} /home/ubuntu/allwpilib.20200121.1500/build/lib/libntcore.so /usr/lib/aarch64-linux-gnu/libpthread.so)
  add_definitions(-Wall -std=c++17 -lstdc++ -lntcore -lopencv_highgui -lopencv_core -lpthread)

Code changes made to ic_pipeline.cpp to publish the stream in the relevant section of the network tables and also to feed the Mat image frames into the MJPEGWriter object.

Code still builds in the normal way ...

  cd /home/ubuntu/Projects/2020.Roley.Vision
  rm -rf build/*
  cd build
  cmake ..
  make
