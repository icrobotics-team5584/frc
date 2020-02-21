#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "GripPipeline.h"
#include <ctime>
#include <iostream>
#include <fstream>

#include <chrono>
#include <cstdio>
#include <thread>
#include "ntcore.h"

#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableInstance.h"

#include "MJPEGWriter.h"
#include "string.h"

using namespace cv;
using namespace std;

VideoCapture cap("/dev/v4l/by-path/platform-70090000.xusb-usb-0:2.1:1.0-video-index0");
Mat frame;

void vidCap0() {

  //input.set(cv::CAP_PROP_FRAME_WIDTH, smallFrame[0]);
  //input.set(cv::CAP_PROP_FRAME_HEIGHT, smallFrame[1]);
  //input.set(cv::CAP_PROP_FPS, 20);

  while (true)
  {
    //m.lock();
    if(!cap.read(frame))
        break;
    //m.unlock();
  }
}

int main()
{
    MJPEGWriter test(7777); //Creates the MJPEGWriter class to stream on the given port
    cap.read(frame);
    test.write(frame); //Writes a frame (Mat class from OpenCV) to the server
    frame.release();

    thread t1(vidCap0);
    test.start(); //Starts the HTTP Server on the selected port
    while(cap.isOpened()){
        if(!cap.read(frame))
          break;
        test.write(frame); 
        frame.release();
    }
    test.stop(); //Stops the HTTP Server
    exit(0);

}


