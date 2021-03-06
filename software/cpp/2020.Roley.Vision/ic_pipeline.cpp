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

// #include "MJPEGWriter.h"
#include "string.h"

using namespace cv;
using namespace std;


cv::Mat img;
// cv::Mat img2;
// cv::Mat img3;
// cv::Mat img4;

int largeFrame[] = { 320, 240 };
int smallFrame[] = { 160, 120 };

int ntVariable = 1;



// Start the camera server on port 5800.
// MJPEGWriter test(5800);
// MJPEGWriter test2(5801);
// MJPEGWriter test3(5802);

cv::Mat blankMat;

// std::mutex m;



RNG rng(12345);
int peg_hits = 0;
int peg_misses = 0;
int debug = 0;

int stream0 = 0;
int stream1 = 1;

void vidCap0() {
  cv::VideoCapture input("/dev/v4l/by-path/platform-70090000.xusb-usb-0:2.1:1.0-video-index0");

  input.set(cv::CAP_PROP_FRAME_WIDTH, smallFrame[0]);
  input.set(cv::CAP_PROP_FRAME_HEIGHT, smallFrame[1]);
  //input.set(cv::CAP_PROP_FPS, 20);

  while (true)
  {
    //m.lock();
    if(!input.read(img))
        break;
    //m.unlock();
  }
}

// void vidCap1() {
//   cv::VideoCapture input2("/dev/video1");
//   //int streamer1 = 0;
//   int lastNtVariable = 1;

//   input2.set(cv::CAP_PROP_FRAME_WIDTH, largeFrame[0]);
//   input2.set(cv::CAP_PROP_FRAME_HEIGHT, largeFrame[1]);
//   //input2.set(cv::CAP_PROP_FPS, 20);

//   while (true)
//   {
//     //streamer1 = nt->GetNumber("Cam 0", 0);
//     //m.lock();
//     if(!input2.read(img2))
//       break;
//     //m.unlock();
  
//     if (ntVariable != lastNtVariable) {
//       if      (ntVariable == 0) {
//         input2.set(cv::CAP_PROP_FRAME_WIDTH, smallFrame[0]);
//         input2.set(cv::CAP_PROP_FRAME_HEIGHT, smallFrame[1]);
//       }
//       else if (ntVariable == 1) { 
//         input2.set(cv::CAP_PROP_FRAME_WIDTH, largeFrame[0]);
//         input2.set(cv::CAP_PROP_FRAME_HEIGHT, largeFrame[1]);
//       }
//       else if (ntVariable == 2) {
//         input2.set(cv::CAP_PROP_FRAME_WIDTH, smallFrame[0]);
//         input2.set(cv::CAP_PROP_FRAME_HEIGHT, smallFrame[1]);
//       }
//       else if (ntVariable == 3) {
//         input2.set(cv::CAP_PROP_FRAME_WIDTH, smallFrame[0]);
//         input2.set(cv::CAP_PROP_FRAME_HEIGHT, smallFrame[1]);
//       }
//     }

//     lastNtVariable = ntVariable;
//   }
// }

// void vidCap2() {
//   cv::VideoCapture input3("/dev/video2");
//   //int streamer2 = 0;
//   int lastNtVariable = 1;


//   input3.set(cv::CAP_PROP_FRAME_WIDTH, smallFrame[0]);
//   input3.set(cv::CAP_PROP_FRAME_HEIGHT, smallFrame[1]);
//   //input3.set(cv::CAP_PROP_FPS, 20);

//   while (true)
//   {
//     //streamer2 = nt->GetNumber("Cam 0", 0);

//     //m.lock();
//     if(!input3.read(img3))
//       break;
//     //m.unlock();
//     if (ntVariable != lastNtVariable) {
//       if      (ntVariable == 0) {
//         input3.set(cv::CAP_PROP_FRAME_WIDTH, smallFrame[0]);
//         input3.set(cv::CAP_PROP_FRAME_HEIGHT, smallFrame[1]);
//       }
//       else if (ntVariable == 1) { 
//         input3.set(cv::CAP_PROP_FRAME_WIDTH, smallFrame[0]);
//         input3.set(cv::CAP_PROP_FRAME_HEIGHT, smallFrame[1]);
//       }
//       else if (ntVariable == 2) {
//         input3.set(cv::CAP_PROP_FRAME_WIDTH, largeFrame[0]);
//         input3.set(cv::CAP_PROP_FRAME_HEIGHT, largeFrame[1]);
//       }
//       else if (ntVariable == 3) {
//         input3.set(cv::CAP_PROP_FRAME_WIDTH, smallFrame[0]);
//         input3.set(cv::CAP_PROP_FRAME_HEIGHT, smallFrame[1]);
//       }
//     }
//   }
// }

// void vidCap3() {
//   cv::VideoCapture input4("/dev/video3");
//   //int streamer3 = 0;
//   int lastNtVariable = 1;


//   input4.set(cv::CAP_PROP_FRAME_WIDTH, smallFrame[0]);
//   input4.set(cv::CAP_PROP_FRAME_HEIGHT, smallFrame[1]);
//   //input4.set(cv::CAP_PROP_FPS, 20);

//   while (true)
//   {
//     //streamer3 = nt->GetNumber("Cam 0", 0);

//     //m.lock();
//     if(!input4.read(img4))
//       break;
//     //m.unlock();

//     if (ntVariable != lastNtVariable) {
//       if      (ntVariable == 0) {
//         input4.set(cv::CAP_PROP_FRAME_WIDTH, smallFrame[0]);
//         input4.set(cv::CAP_PROP_FRAME_HEIGHT, smallFrame[1]);
//       }
//       else if (ntVariable == 1) { 
//         input4.set(cv::CAP_PROP_FRAME_WIDTH, smallFrame[0]);
//         input4.set(cv::CAP_PROP_FRAME_HEIGHT, smallFrame[1]);
//       }
//       else if (ntVariable == 2) {
//         input4.set(cv::CAP_PROP_FRAME_WIDTH, smallFrame[0]);
//         input4.set(cv::CAP_PROP_FRAME_HEIGHT, smallFrame[1]);
//       }
//       else if (ntVariable == 3) {
//         input4.set(cv::CAP_PROP_FRAME_WIDTH, largeFrame[0]);
//         input4.set(cv::CAP_PROP_FRAME_HEIGHT, largeFrame[1]);
//       }
//     }
//   }
// }

// void stream()
// {
//   int streamer = 0;

//     // setup network tables connection

//     std::this_thread::sleep_for(std::chrono::seconds(5));

//     // setup network tables for camera location settings.
//     //auto ntcam = NetworkTable::GetTable("CameraPublisher/CVCamera");
//     //ntcam->SetClientMode();
//     //ntcam->SetIPAddress("10.55.84.2\n");
//     //ntcam->Initialize();



    
//     test.start();
//     test2.start();
//     test3.start();

//     std::cout << "Camera Servers started." << std::endl;

//     //nt->PutNumber("Cam 1", 1);

//   while(true)
//   {
//     //streamer = nt->GetNumber("Cam 0", 0);

//     //m.lock();
//     if      (ntVariable == 0) {
//       //std::cout << "CONDITION 0 MET" << std::endl;
//       test.write(img);

//       test2.write(img2);
//       test3.write(img3);
//       }
//     else if (ntVariable == 1) { 
//       //std::cout << "CONDITION 1 MET" << std::endl;
//       test.write(img2);

//       test2.write(img3);
//       test3.write(img4);
//     }
//     else if (ntVariable == 2) {
//       //std::cout << "CONDITION 2 MET" << std::endl;
//       test.write(img3);

//       test2.write(img2);
//       test3.write(img4);
//     }
//     else if (ntVariable == 3) {
//       //std::cout << "CONDITION 3 MET" << std::endl;
//       test.write(img4);

//       test2.write(img2);
//       test3.write(img3);
//     }
//     //m.unlock();

//   }
// }

int main( int argc, char *argv[] )
{
  // handle command line arguments
  if( ( argc > 1 ) && ( strcmp( argv[1], "--debug" ) == 0 ) )
    debug = 1;

  // setup image pipeline
  

  //cv::Mat images[4] = { img, img2, img3, img4 };

  //cv::GpuMat g_img(img);
  grip::GripPipeline ic_pipeline;

  // setup network tables connection
  nt::NetworkTableInstance ntinst = nt::NetworkTableInstance::GetDefault();
  std::shared_ptr<nt::NetworkTable> nt;
  nt = ntinst.GetTable("JETSON");
  ntinst.StartClientTeam(5584);
  std::this_thread::sleep_for(std::chrono::seconds(5));

  nt->PutNumber("Cam 0", 1);


std::shared_ptr<nt::NetworkTable> ntcam;
ntcam = ntinst.GetTable("CameraPublisher/CVCamera");

std::shared_ptr<nt::NetworkTable> ntcam2;
ntcam2 = ntinst.GetTable("CameraPublisher/CVCamera2");

std::shared_ptr<nt::NetworkTable> ntcam3;
ntcam3 = ntinst.GetTable("CameraPublisher/CVCamera3");

std::this_thread::sleep_for(std::chrono::seconds(5));  std::cout << "Network Tables Initialized." << std::endl;
// Put IP Address Values into CameraPublisher NetworkTable
string Fred[1] = {"mjpeg:http://10.55.84.8:5800/?action=stream"}; //Fred and James are the camera ip address arrays. They have to be there for the camera server to work.
ntcam->PutStringArray("streams", Fred);

string James[1] = {"mjpeg:http://10.55.84.8:5801"};
ntcam2->PutStringArray("streams", James);

string Max[1] = {"mjpeg:http://10.55.84.8:5802"};
ntcam3->PutStringArray("streams", Max);

std::cout << "Arrays pushed to network tables." << std::endl;


  // record start time
  clock_t start = clock();

  
  thread t1(vidCap0);
  // thread t2(vidCap1);
  // thread t3(vidCap2);
  // thread t4(vidCap3);

  while (empty(img))  {}
  // while (empty(img2)) {}
  // while (empty(img3)) {}
  // while (empty(img4)) {}

  // thread t5(stream);

  for (;;)
  {
    
    std::cout << "Stream 0: " << stream0 << std::endl;


    // STEP 1: fetch image


    // STEP 2: setup image pipeline
    //ic_pipeline.setsource0(img);
    ic_pipeline.Process(img);

    // STEP 3: obtain intermediate images and countour vectors
    cv::Mat* img_hsvthreshold = ic_pipeline.GetHsvThresholdOutput();
    cv::Mat* img_blur = ic_pipeline.GetBlurOutput();
    // std::vector<std::vector<cv::Point> >* img_findcontours = ic_pipeline.GetFindContoursOutput();
    std::vector<std::vector<cv::Point> >* img_filtercontours = ic_pipeline.GetFilterContoursOutput();

    // STEP 4: output contour x, y, width and height
    cout << "INFO: bounding rectangles for each contour: (x,y):(width,height)" << endl;
    for (std::vector<cv::Point> contour: *img_filtercontours)
    {
      cv::Rect br = boundingRect(contour);
      cout << "(" << br.x << "," << br.y << "):(" << br.width << "," << br.height << ")" << endl;
    }

    // STEP 5: construct image to display filetered contours, bounding rectangles and origins of rectangles
    cv::Mat img_contours = cv::Mat::zeros( cv::Size(320, 180), CV_8UC3 );
    int img_width = 320;  //img.size().width;
    int img_height = 180; //img.size().height;
    for( size_t i = 0; i< img_filtercontours->size(); i++ )
     {
       Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
       drawContours( img_contours, *img_filtercontours, (int)i, color, 2, 8 );
     }
    int contourcount = 0;
    int min_x = 1000000;
    int max_x = 0;
    int min_y = 1000000;
    int max_y = 0;
    double peg_x = 0.0;
    double peg_y = 0.0;
    double range_x = 0.0;
    double peg_range = 0.0;
    double bounding_rectangle_width = 0.0;
    double bounding_rectangle_height = 0.0;
    for (std::vector<cv::Point> contour: *img_filtercontours)
    {
      Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
      cv::Rect br = boundingRect(contour);
      cv::rectangle( img_contours, br, color, 2, 8 );
      Point origin;
      origin.x = br.x;
      origin.y = br.y;
      cv::circle( img_contours, origin, 5, color, 2, 8 );
      int topleft_x = br.x;
      int topleft_y = br.y;
      int bottomright_x = br.x + br.width;
      int bottomright_y = br.y + br.height;
      if( topleft_x < min_x ) { min_x = topleft_x; }
      if( topleft_y < min_y ) { min_y = topleft_y; }
      if( bottomright_x > max_x ) { max_x = bottomright_x; }
      if( bottomright_y > max_y ) { max_y = bottomright_y; }
      contourcount++;
    }
    int status;
    cout << "INFO: number of contours detected: " << contourcount << endl;
    if( contourcount == 1 )
    {
      status = 0;
      peg_hits++;
      double x = ( min_x + max_x ) / 2;
      double y = min_y;
      cout << "INFO: estimated peg position in image: (x,y)" << endl;
      cout << "(" << x << "," << y << ")" << endl;
      bounding_rectangle_width = 1.0 * (max_x - min_x) / img_width;
      bounding_rectangle_height = 1.0 * (max_y - min_y) / img_height;
      cout << "INFO: bounding rectangle size as proportion of FOV: (width,height)" << endl;
      cout << "(" << bounding_rectangle_width << "," << bounding_rectangle_height << ")" << endl;
      // calculate peg postion with image center (0,0) and bottom left (-1,-1) and top right (+1,+1)
      peg_x = 30 * ( x - ( img_width / 2 ) ) / ( img_width / 2 );
      peg_y = -17 * ( y - ( img_height / 2 ) ) / ( img_height / 2 );
      cout << "INFO: estimated peg position in field of view: (x,y)" << endl;
      cout << "(" << peg_x << "," << peg_y << ")" << endl;
      // estimate range based on prior knowledge of camera vertical FOV and  420mm target height
      range_x = (max_y - min_y);
      peg_range = (0.0009 * range_x * range_x) - (0.1845 * range_x) + 9.7792;
      
      cout << "INFO: estimated peg range: (mm)" << endl;
      cout << peg_range << "mm" << endl;
      // display peg position at x, y on contours image ...
      Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
      Point peg;
      peg.x = x;
      peg.y = y;
      cv::circle( img_contours, peg, 10, color, 2, 8 );
    }
    else
    {
      status = 1;
      peg_misses++;
      peg_x = 0.0; 
      peg_y = 0.0;
      peg_range = 0.0;
      bounding_rectangle_width = 0.0;
      bounding_rectangle_height = 0.0;
      cout << "INFO: unable to detect peg position" << endl;
    }
    double peg_hitrate = ( 100.0 * peg_hits ) / ( peg_misses + peg_hits );
    cout << "INFO: peg position detections so far: " << peg_hits << " (" << peg_misses << ") (" << peg_hitrate << "% hitrate)" << endl;
    clock_t now = clock();
    double elapsedsecs = ( now - start ) / (double) CLOCKS_PER_SEC;
    double fps = (double) 1.0 / elapsedsecs;
    start = now;
    cout << "INFO: elapsed seconds since last frame: " << elapsedsecs << endl;
    cout << "INFO: frames per second: " << fps << endl;

    // STEP 6: display images
    if( debug == 1 )
    {
      cv::imshow( "img", img );
      // cv::imshow( "img2", img2 );
      // cv::imshow( "img3", img3 );
      // cv::imshow( "img4", img4 );
      cv::imshow( "hsv threshold", *img_hsvthreshold );
      cv::imshow( "blur", *img_blur );
      cv::imshow( "img_contours", img_contours );
    }

    // STEP 7: update network tables
    cout << "INFO: updating network tables" << endl;
    nt->PutNumber( "status", status );
    nt->PutNumber( "timestamp", (int)now );
    nt->PutNumber( "pegx", peg_x );
    nt->PutNumber( "pegy", peg_y );
    nt->PutNumber( "pegrange", peg_range );
    nt->PutNumber( "boundingrectangleheight", bounding_rectangle_height );
    nt->PutNumber( "boundingrectanglewidth", bounding_rectangle_width );
    nt->PutNumber( "hitrate", peg_hitrate );
    nt->PutNumber( "elapsedsecs", elapsedsecs );
    nt->PutNumber( "fps", fps );
    cout << "-----" << endl;

    // STEP 7.5: Do some camera server things
    std::cout << "About to push camera frames to server." << std::endl;

    // ntVariable = nt->GetNumber("Cam 0", 0);
    // stream1 = nt->GetNumber("Cam 1", 1);
    
    
    
    // if      (stream1 == 0) { test2.write(img); }
    // else if (stream1 == 1) { test2.write(img2); }
    // else if (stream1 == 2) { test2.write(img3); }
    // else if (stream1 == 3) { test2.write(img4); }

    //test.write(img);
    //test2.write(img2);
    //test3.write(img3);

    img_contours.release();
    std::cout << "Frame 1 pushed to server." << std::endl;
//    test2.write(img_contours);
    img_contours.release();
    std::cout << "Frame 5584 pushed to server." << std::endl;

    // STEP 8: check for control file
    string line;
    ifstream ctlfile1("ic_pipeline.stop");
    ifstream ctlfile2("/tmp/ic_pipeline.stop");
    int running = 1; 
    if( ctlfile1.is_open() || ctlfile2.is_open() )
    {
      running = 0;
      ctlfile1.close();
      ctlfile2.close();
    }
    if( running == 0 )
    {
      cout << "INFO: detected control file (stop)" << endl;
      // test.stop();
      // test2.stop();
      // test3.stop();

      t1.join();
      // t2.join();
      // t3.join();
      // t4.join();
      // t5.join();
      break;
    }

    // STEP 9: check for user request to terminate
    char c = cv::waitKey(30);
    if ( c == ' ' )
      break;

  }

}


