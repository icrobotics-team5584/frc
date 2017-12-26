README.TXT
==========

These notes describe how to set up, build and use an image pipeline that was generated using the GRIP program. The target system in this case is an Nvidia Jetson TK1 development board.



PREREQUISITES
-------------

Nvidia Jetson TK1 plus Microsoft HD3000 webcam.

TK1 needs imaging, this is easiest achived using the Nvidia Jetpack, this is easiest achived using the Nvidia Jetpack - instructions for this task are out of scope for these notes.



PREPARATION
-----------

Unzip to a project folder e.g. /home/ubuntu/ic_pipeline

If necessary, use GRIP to generate new GripPipeline.h and GripPipeline.cpp.

If GripPipeline has more than parameter changes then you will need to mofify ic_pipeline.cpp to handle the changes.

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



AUTOMATED EXECUTION ON BOOT
---------------------------

Create a script at /home/ubuntu/9-ic-pipeline/ic_pipeline.sh

With content:

  #!/bin/bash
  # setup camera
  /usr/bin/v4l2-ctl --set-ctrl exposure_auto=1
  /usr/bin/v4l2-ctl --set-ctrl exposure_absolute=5
  # purge old log file
  /bin/rm -f /tmp/ic_pipeline.log
  # run application
  cd /home/ubuntu/9-ic-pipeline/build
  ./ic_pipeline >> /tmp/ic_pipeline.log 2>&1

Add this line to the ubuntu user's crontab ...

  @reboot /bin/sleep 60; /home/ubuntu/9-ic-pipeline/ic_pipeline.sh

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




==============================
Other little coding notes
==============================

ctrl ^ z  		:stops running current program 
fg  			:resumes programs 
./   ./ic_blah --debug	:runs a program  
nohup ./     		: runs the program in shell on the jetson
ctrl z			: interupts the current program   
bg			: moves the program to the background    
TAB   			:fills the rest 
sudo reboot     	:reboots the jetson  
cd   	       	        :goes into the directory of which you type after cd 
cd ..   		:goes back a directory 
ps -e | grep "ic"       :finds things running with [ic] in it 
touch ic_piepline.stop  :is our thing for stopping the ic pipeline this is in directory build.... note! if using (nohup) then add the ic,stop 													file in the ubuntu tmp directory!
xeyes   		:tests xming 
ifconfig -a   		:linux all adpaters 
rm 			:to remove ######  <-- a file 
vim 			:allows edditing of code   to get out  -->  holdShift :double tap (ZZ)
pwd 		        :lists current directory


+++++++++++
Networking 
+++++++++++
sudo ifconfig eth0 192.168.0.1 netmask 255.255.255.0   :changes ip on linux      ip to change to 10.55.84.8  (for 5584)

for changing the ip perm    goto   etc/network    use vim to eddit "interfaces" then change ips 

access roboreo   roborio-5584-frc.local

 

===============================
scp :transmitting file remotly
===============================


scp 

echo test >> test.txt   :puts "test" into new file called "test.txt"

>			:add thing into file or something 

>> 			:add it to the end of whatever is in file or something
 
../downlaods 		:the dot , dot looks up an directory 


scp test.txt ubuntu@10.55.84.8:/tmp    			:from your computer to the jetson 

scp ubuntu@10.55.84.8:/tmp/test2.txt ../Downloads/      :from the jetson to your computer 


scp ubuntu@10.55.84.8:/home/ubuntu/9-ic-pipeline/ic_pipeline.cpp c:/scm/

scp ubuntu@10.55.84.8:/home/ubuntu/9-ic-pipeline/ic_pipeline.cpp ../Downloads/



for an directory [scp -r ubuntu@.....]

$ scp -r ubuntu@10.55.84.8:/home/ubuntu/9-ic-pipeline ../Downloads/




========================================
Editing shell files on the Jettson 
========================================
crontab -l	:this views contents of shell file 

crontab -e 	:this eddits contents of shell file

