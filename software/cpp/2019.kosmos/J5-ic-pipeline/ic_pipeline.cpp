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

using namespace cv;
using namespace std;

RNG rng(12345);
int tgt_hits = 0;
int tgt_misses = 0;
double tgt_x = 0;
double tgt_y = 0;
double tgt_range = 0;
int debug = 0;

int main( int argc, char *argv[] )
{

  // handle command line arguments
  if( ( argc > 1 ) && ( strcmp( argv[1], "--debug" ) == 0 ) )
    debug = 1;

  // setup image pipeline
  cv::Mat img0;
  cv::Mat img1;
  cv::Mat img2;
  cv::Mat img3;
  grip::GripPipeline ic_pipeline;
  cv::VideoCapture input0(0);
  cv::VideoCapture input1(1);
  cv::VideoCapture input2(2);
  cv::VideoCapture input3(3);

  // record start time
  clock_t start = clock();

  // setup network tables connection
  auto nt = NetworkTable::GetTable("JETSON");
  nt->SetClientMode();
  nt->SetIPAddress("10.55.84.2\n");
  nt->Initialize();
  std::this_thread::sleep_for(std::chrono::seconds(5));

  for (;;)
  {

    // STEP 1: fetch images
    if(!input0.read(img0))
      break;
    if(!input1.read(img1))
      break;
    if(!input2.read(img2))
      break;
    if(!input3.read(img3))
      break;

    // STEP 2: setup image pipeline
    ic_pipeline.SetSource0(img0);
    ic_pipeline.SetSource1(img1);
    ic_pipeline.SetSource2(img2);
    ic_pipeline.SetSource3(img3);
    ic_pipeline.Process(img0, img1, img2, img3);

    // STEP 3: obtain intermediate images and countour vectors
    cv::Mat* img_hsvthreshold0 = ic_pipeline.GetHsvThreshold0Output();
    cv::Mat* img_hsvthreshold1 = ic_pipeline.GetHsvThreshold1Output();
    cv::Mat* img_rgbthreshold0 = ic_pipeline.GetRgbThreshold0Output();
		cv::Mat* img_rgbthreshold1 = ic_pipeline.GetRgbThreshold1Output();
   
		//cv::Mat* img_switchOutput0 = ic_pipeline.GetSwitch0Output();
		//cv::Mat* img_switchOutput1 = ic_pipeline.GetSwitch1Output();
    //std::vector<std::vector<cv::Point> >* img_switchOutput2 = ic_pipeline.GetSwitch2Output();
		//std::vector<std::vector<cv::Point> >* img_switchOutput3 = ic_pipeline.GetSwitch3Output();
   
    cv::Mat* img_blur0 = ic_pipeline.GetBlur0Output();
    cv::Mat* img_blur1 = ic_pipeline.GetBlur1Output();
    
    // std::vector<std::vector<cv::Point> >* img_findcontours0 = ic_pipeline.GetFindContours0Output();
    // std::vector<std::vector<cv::Point> >* img_findcontours1 = ic_pipeline.GetFindContours1Output();
    
    std::vector<std::vector<cv::Point> >* img_filtercontours0 = ic_pipeline.GetFilterContours0Output();
    std::vector<std::vector<cv::Point> >* img_filtercontours1 = ic_pipeline.GetFilterContours1Output();
    std::vector<std::vector<cv::Point> >* img_filtercontours2 = ic_pipeline.GetFilterContours2Output();
    std::vector<std::vector<cv::Point> >* img_filtercontours3 = ic_pipeline.GetFilterContours3Output();
    
    
    

    // STEP 4: output contour x, y, width and height
    cout << "INFO: bounding rectangles for each contour: (x,y):(width,height)" << endl;
    for (std::vector<cv::Point> contour: *img_filtercontours0)
    {
      cv::Rect br = boundingRect(contour);
      cout << "Camera 0 (" << br.x << "," << br.y << "):(" << br.width << "," << br.height << ")" << endl;
    }
    
        for (std::vector<cv::Point> contour: *img_filtercontours2)
    {
      cv::Rect br = boundingRect(contour);
      cout << "Camera 1(" << br.x << "," << br.y << "):(" << br.width << "," << br.height << ")" << endl;
    }
    
        for (std::vector<cv::Point> contour: *img_filtercontours1)
    {
      cv::Rect br = boundingRect(contour);
      cout << "Camera 2(" << br.x << "," << br.y << "):(" << br.width << "," << br.height << ")" << endl;
    }
    
        for (std::vector<cv::Point> contour: *img_filtercontours3)
    {
      cv::Rect br = boundingRect(contour);
      cout << "Camera 3(" << br.x << "," << br.y << "):(" << br.width << "," << br.height << ")" << endl;
    }

    // STEP 5: construct images to display filetered contours, bounding rectangles and origins of rectangles
    cv::Mat img_contours0 = cv::Mat::zeros( img0.size(), CV_8UC3 );
    int img_width0 = img0.size().width;
    int img_height0 = img0.size().height;
    for( size_t i = 0; i< img_filtercontours0->size(); i++ )
     {
       Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
       drawContours( img_contours0, *img_filtercontours0, (int)i, color, 2, 8 );
     }
    int contourcount0 = 0;
    int min_x0 = 1000000;
    int max_x0 = 0;
    int min_y0 = 1000000;
    int max_y0 = 0;
    double tgt_x0 = 0.0;
    double tgt_y0 = 0.0;
    double tgt_range0 = 0.0;
    double bounding_rectangle_width0 = 0.0;
    double bounding_rectangle_height0 = 0.0;
    for (std::vector<cv::Point> contour: *img_filtercontours0)
    {
      Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
      cv::Rect br = boundingRect(contour);
      cv::rectangle( img_contours0, br, color, 2, 8 );
      Point origin;
      origin.x = br.x;
      origin.y = br.y;
      cv::circle( img_contours0, origin, 5, color, 2, 8 );
      int topleft_x = br.x;
      int topleft_y = br.y;
      int bottomright_x = br.x + br.width;
      int bottomright_y = br.y + br.height;
      if( topleft_x < min_x0 ) { min_x0 = topleft_x; }
      if( topleft_y < min_y0 ) { min_y0 = topleft_y; }
      if( bottomright_x > max_x0 ) { max_x0 = bottomright_x; }
      if( bottomright_y > max_y0 ) { max_y0 = bottomright_y; }
      contourcount0++;
    }
    
    cv::Mat img_contours1 = cv::Mat::zeros( img1.size(), CV_8UC3 );
    int img_width1 = img1.size().width;
    int img_height1 = img1.size().height;
    for( size_t i = 0; i< img_filtercontours2->size(); i++ )
     {
       Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
       drawContours( img_contours1, *img_filtercontours2, (int)i, color, 2, 8 );
     }
    int contourcount1 = 0;
    int min_x1 = 1000000;
    int max_x1 = 0;
    int min_y1 = 1000000;
    int max_y1 = 0;
    double tgt_x1 = 0.0;
    double tgt_y1 = 0.0;
    double tgt_range1 = 0.0;
    double bounding_rectangle_width1 = 0.0;
    double bounding_rectangle_height1 = 0.0;
    for (std::vector<cv::Point> contour: *img_filtercontours2)
    {
      Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
      cv::Rect br = boundingRect(contour);
      cv::rectangle( img_contours1, br, color, 2, 8 );
      Point origin;
      origin.x = br.x;
      origin.y = br.y;
      cv::circle( img_contours1, origin, 5, color, 2, 8 );
      int topleft_x = br.x;
      int topleft_y = br.y;
      int bottomright_x = br.x + br.width;
      int bottomright_y = br.y + br.height;
      if( topleft_x < min_x1 ) { min_x1 = topleft_x; }
      if( topleft_y < min_y1 ) { min_y1 = topleft_y; }
      if( bottomright_x > max_x1 ) { max_x1 = bottomright_x; }
      if( bottomright_y > max_y1 ) { max_y1 = bottomright_y; }
      contourcount1++;
    }

    cv::Mat img_contours2 = cv::Mat::zeros( img2.size(), CV_8UC3 );
    //int img_width2 = img2.size().width;
    //int img_height2 = img2.size().height;
    for( size_t i = 0; i< img_filtercontours1->size(); i++ )
     {
       Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
       drawContours( img_contours2, *img_filtercontours1, (int)i, color, 2, 8 );
     }
    int contourcount2 = 0;
    int min_x2 = 1000000;
    int max_x2 = 0;
    int min_y2 = 1000000;
    int max_y2 = 0;
    //double tgt_x1 = 0.0;
    //double tgt_y1 = 0.0;
    //double tgt_range1 = 0.0;
    //double bounding_rectangle_width2 = 0.0;
    //double bounding_rectangle_height2 = 0.0;
    for (std::vector<cv::Point> contour: *img_filtercontours1)
    {
      Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
      cv::Rect br = boundingRect(contour);
      cv::rectangle( img_contours2, br, color, 2, 8 );
      Point origin;
      origin.x = br.x;
      origin.y = br.y;
      cv::circle( img_contours2, origin, 5, color, 2, 8 );
      int topleft_x = br.x;
      int topleft_y = br.y;
      int bottomright_x = br.x + br.width;
      int bottomright_y = br.y + br.height;
      if( topleft_x < min_x2 ) { min_x2 = topleft_x; }
      if( topleft_y < min_y2 ) { min_y2 = topleft_y; }
      if( bottomright_x > max_x2 ) { max_x2 = bottomright_x; }
      if( bottomright_y > max_y2 ) { max_y2 = bottomright_y; }
      contourcount2++;
    }

    cv::Mat img_contours3 = cv::Mat::zeros( img3.size(), CV_8UC3 );
    //int img_width3 = img3.size().width;
    //int img_height3 = img3.size().height;
    for( size_t i = 0; i< img_filtercontours3->size(); i++ )
     {
       Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
       drawContours( img_contours3, *img_filtercontours3, (int)i, color, 2, 8 );
     }
    int contourcount3 = 0;
    int min_x3 = 1000000;
    int max_x3 = 0;
    int min_y3 = 1000000;
    int max_y3 = 0;
    //double tgt_x1 = 0.0;
    //double tgt_y1 = 0.0;
    //double tgt_range1 = 0.0;
    //double bounding_rectangle_width3 = 0.0;
    //double bounding_rectangle_height3 = 0.0;
    for (std::vector<cv::Point> contour: *img_filtercontours3)
    {
      Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
      cv::Rect br = boundingRect(contour);
      cv::rectangle( img_contours3, br, color, 2, 8 );
      Point origin;
      origin.x = br.x;
      origin.y = br.y;
      cv::circle( img_contours3, origin, 5, color, 2, 8 );
      int topleft_x = br.x;
      int topleft_y = br.y;
      int bottomright_x = br.x + br.width;
      int bottomright_y = br.y + br.height;
      if( topleft_x < min_x3 ) { min_x3 = topleft_x; }
      if( topleft_y < min_y3 ) { min_y3 = topleft_y; }
      if( bottomright_x > max_x3 ) { max_x3 = bottomright_x; }
      if( bottomright_y > max_y3 ) { max_y3 = bottomright_y; }
      contourcount3++;
    }

    int status;
    int cargostatus;
    int largest_area0=0;
    int largest_area1=0;
    int largest_contour_index0=0;
    int largest_contour_index1=0;
    
    cout << "INFO: searching for larget contour in camera 0" << endl;
    for( size_t i = 0; i< img_filtercontours0->size(); i++ ) // iterate through each contour. 
    {
      double a=contourArea( (*img_filtercontours0)[i],false);  //  Find the area of contour
      cout << i << ":" << a << endl;
      if(a>largest_area0)
      {
        largest_area0=a;
        largest_contour_index0=i;                //Store the index of largest contour
      }
    }
    cout << "INFO: Index of largest contour of img 0 (and area)" << endl;
    cout << largest_contour_index0 << " (" << largest_area0 << ")" << endl;
     
    cout << "INFO: searching for larget contour in camera 1" << endl;
    for( size_t i = 0; i< img_filtercontours2->size(); i++ ) // iterate through each contour. 
    {
      double a=contourArea( (*img_filtercontours2)[i],false);  //  Find the area of contour
      cout << i << ":" << a << endl;
      if(a>largest_area1)
      {
        largest_area1=a;
        largest_contour_index1=i;                //Store the index of largest contour
      }
    }
    cout << "INFO: Index of largest contour of img 1 (and area)" << endl;
    cout << largest_contour_index1 << " (" << largest_area1 << ")" << endl;
    
     
    if( ( contourcount0 != 0 ) && ( contourcount1 != 0 ) )
    {
      status = 0;
      tgt_hits++;

      cv::Rect br0 = boundingRect((*img_filtercontours0)[largest_contour_index0]);
      int topleft_x0 = br0.x;
      int topleft_y0 = br0.y;
      int bottomright_x0 = br0.x + br0.width;
      int bottomright_y0 = br0.y + br0.height;
      double x0 = (topleft_x0 + bottomright_x0) / 2;
      double y0 = (topleft_y0 + bottomright_y0) / 2;
      cout << "INFO: estimated tgt position in image: (x0,y0)" << endl;
      cout << "(" << x0 << "," << y0 << ")" << endl;
      bounding_rectangle_width0 = 1.0 * br0.width / img_width0;
      bounding_rectangle_height0 = 1.0 * br0.height / img_height0;
      cout << "INFO: bounding rectangle size as proportion of FOV: (width0,height0)" << endl;
      cout << "(" << bounding_rectangle_width0 << "," << bounding_rectangle_height0 << ")" << endl;

      cv::Rect br1 = boundingRect((*img_filtercontours2)[largest_contour_index1]);
      int topleft_x1 = br1.x;
      int topleft_y1 = br1.y;
      int bottomright_x1 = br1.x + br1.width;
      int bottomright_y1 = br1.y + br1.height;
      double x1 = (topleft_x1 + bottomright_x1) / 2;
      double y1 = (topleft_y1 + bottomright_y1) / 2;
      cout << "INFO: estimated tgt position in image: (x1,y1)" << endl;
      cout << "(" << x1 << "," << y1 << ")" << endl;
      bounding_rectangle_width1 = 1.0 * br1.width / img_width1;
      bounding_rectangle_height1 = 1.0 * br1.height / img_height1;
      cout << "INFO: bounding rectangle size as proportion of FOV: (width1,height1)" << endl;
      cout << "(" << bounding_rectangle_width1 << "," << bounding_rectangle_height1 << ")" << endl;

      // calculate tgt postion with image center (0,0) and bottom left (-1,-1) and top right (+1,+1)
      tgt_x0 = ( x0 - ( img_width0 / 2 ) ) / ( img_width0 / 2 );
      tgt_y0 = -1 * ( y0 - ( img_height0 / 2 ) ) / ( img_height0 / 2 );
      cout << "INFO: estimated tgt position in field of view: (x0,y0)" << endl;
      cout << "(" << tgt_x0 << "," << tgt_y0 << ")" << endl;
      tgt_x1 = ( x1 - ( img_width1 / 2 ) ) / ( img_width1 / 2 );
      tgt_y1 = -1 * ( y1 - ( img_height1 / 2 ) ) / ( img_height1 / 2 );
      cout << "INFO: estimated tgt position in field of view: (x1,y1)" << endl;
      cout << "(" << tgt_x1 << "," << tgt_y1 << ")" << endl;

      tgt_x = ( tgt_x0 + tgt_x1 ) / 2;
      tgt_y = ( tgt_y0 + tgt_y1 ) / 2;
      cout << "INFO: fused tgt position in field of view: (x,y)" << endl;
      cout << "(" << tgt_x << "," << tgt_y << ")" << endl;

      // estimate range based on prior knowledge of camera horizontal FOV and target height assume 60 degree (1.047 radian) horizontal FOV and 140mm target height
      tgt_range0 = 140 / tan( 1.047 * ( max_y0 - min_y0 ) / img_height0 );
      cout << "INFO: estimated tgt range0: (mm)" << endl;
      cout << tgt_range0 << "mm" << endl;
      tgt_range1 = 140 / tan( 1.047 * ( max_y1 - min_y1 ) / img_height1 );
      cout << "INFO: estimated tgt range1: (mm)" << endl;
      cout << tgt_range1 << "mm" << endl;

      tgt_range = ( tgt_range0 + tgt_range1 ) / 2;
      cout << "INFO: fused tgt range: (mm)" << endl;
      cout << tgt_range << "mm" << endl;

      // display tgt position at x, y on contours image ...
      Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
      Point tgt0;
      tgt0.x = x0;
      tgt0.y = y0;
      cv::circle( img_contours0, tgt0, 10, color, 2, 8 );
      Point tgt1;
      tgt1.x = x1;
      tgt1.y = y1;
      cv::circle( img_contours1, tgt1, 10, color, 2, 8 );
    }
    else
    {
      status = 1;
      tgt_misses++;
      tgt_x0 =0.0; 
      tgt_x1 =0.0; 
      tgt_x =0.0; 
      tgt_y0 = 0.0;
      tgt_y1 = 0.0;
      tgt_y = 0.0;
      tgt_range0 = 0.0;
      tgt_range1 = 0.0;
      tgt_range = 0.0;
      bounding_rectangle_width0 = 0.0;
      bounding_rectangle_width1 = 0.0;
      bounding_rectangle_height0 = 0.0;
      bounding_rectangle_height1 = 0.0;
      cout << "INFO: unable to detect tgt position" << endl;
    }
    
    if( ( contourcount2 != 0 ) && ( contourcount3 != 0 ) )
    {
      cargostatus = 0;
    }
    else
    {
      cargostatus = 1;
    }

    double tgt_hitrate = ( 100.0 * tgt_hits ) / ( tgt_misses + tgt_hits );
    cout << "INFO: tgt position detections so far: " << tgt_hits << " (" << tgt_misses << ") (" << tgt_hitrate << "% hitrate)" << endl;
    clock_t now = clock();
    double elapsedsecs = ( now - start ) / (double) CLOCKS_PER_SEC;
    double fps = (double) 1.0 / elapsedsecs;
    start = now;
    cout << "INFO: elapsed seconds since last frame: " << elapsedsecs << endl;
    cout << "INFO: frames per second: " << fps << endl;

    // STEP 6: display images
    if( debug == 1 )
    {
      cv::imshow( "img0", img0 );
      cv::imshow( "img1", img1 );
      cv::imshow( "img2", img2 );
      cv::imshow( "img3", img3 );
      cv::imshow( "hsvthreshold0", *img_hsvthreshold0 );
      cv::imshow( "hsvthreshold1", *img_hsvthreshold1 );
      cv::imshow( "rgbthreshold1", *img_rgbthreshold0 );
      cv::imshow( "rgbthreshold1", *img_rgbthreshold1 );
      cv::imshow( "blur0", *img_blur0 );
      cv::imshow( "blur1", *img_blur1 );
      cv::imshow( "img_contours 0", img_contours0 );
      cv::imshow( "img_contours 1", img_contours1 );
    }

    // STEP 7: update network tables
    cout << "INFO: updating network tables" << endl;
    //camera 1 and 2 output target reflective
    nt->PutNumber( "status", status );
    nt->PutNumber( "timestamp", (int)now );
    nt->PutNumber( "tgtx", tgt_x );
    nt->PutNumber( "tgty", tgt_y );
    nt->PutNumber( "tgtrange", tgt_range );
    nt->PutNumber( "tgtx0", tgt_x0 );
    nt->PutNumber( "tgty0", tgt_y0 );
    nt->PutNumber( "tgtrange0", tgt_range0 );
    nt->PutNumber( "boundingrectangleheight0", bounding_rectangle_height0 );
    nt->PutNumber( "boundingrectanglewidth0", bounding_rectangle_width0 );
    nt->PutNumber( "tgtx1", tgt_x1 );
    nt->PutNumber( "tgty1", tgt_y1 );
    nt->PutNumber( "tgtrange1", tgt_range1 );
    nt->PutNumber( "boundingrectangleheight1", bounding_rectangle_height1 );
    nt->PutNumber( "boundingrectanglewidth1", bounding_rectangle_width1 );
    nt->PutNumber( "hitrate", tgt_hitrate );
    //camera 3 and 4 output target cargo
    nt->PutNumber( "cargostatus", cargostatus );
    //Fps and Elapsedsecs
    nt->PutNumber( "elapsedsecs", elapsedsecs );
    nt->PutNumber( "fps", fps );
   cout << "-----" << endl;

    // STEP 8: check for control file
    //string line;
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
      break;
    }
    
    
    ifstream ctlfile3("ic_pipeline.mode");
    ifstream ctlfile4("/tmp/ic_pipeline.mode");
    int mode = 1; 
    if( ctlfile1.is_open() || ctlfile2.is_open() )
    {
      mode = 0;
      ctlfile3.close();
      ctlfile4.close();
    }
    if( mode == 0 )
    {
      ic_pipeline.setSwitch0(true);
      ic_pipeline.setSwitch1(true);
      ic_pipeline.setSwitch2(true);
      ic_pipeline.setSwitch3(true);
    }
    else
    {
      ic_pipeline.setSwitch0(false);
      ic_pipeline.setSwitch1(false);
      ic_pipeline.setSwitch2(false);
      ic_pipeline.setSwitch3(false);
    }

    // STEP 9: check for user request to terminate
    char c = cv::waitKey(30);
    if ( c == ' ' )
      break;

  }

}


