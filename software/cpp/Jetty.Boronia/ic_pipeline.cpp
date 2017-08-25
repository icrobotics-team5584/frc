#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "GripPipeline.h"

using namespace cv;
using namespace std;

RNG rng(12345);

int main()
{

  cv::Mat img;

  grip::GripPipeline ic_pipeline;

  cv::VideoCapture input(0);

  for (;;)
  {

    // STEP 1: fetch image
    if(!input.read(img))
      break;

    // STEP 2: setup image pipeline
    ic_pipeline.setsource0(img);
    ic_pipeline.process(img);

    // STEP 3: obtain intermediate images and countour vectors
    cv::Mat* img_hsvthreshold = ic_pipeline.gethsvThresholdOutput();
    cv::Mat* img_blur = ic_pipeline.getblurOutput();
    std::vector<std::vector<cv::Point> >* img_findcontours = ic_pipeline.getfindContoursOutput();
    std::vector<std::vector<cv::Point> >* img_filtercontours = ic_pipeline.getfilterContoursOutput();

    // STEP 4: output contour x, y, width and height
    printf( "INFO: BOUNDING RECTANGLES FOR EACH CONTOUR: (x,y):(width,height)\n" );
    for (std::vector<cv::Point> contour: *img_filtercontours)
    {
      cv::Rect br = boundingRect(contour);
      printf( "(%d,%d):(%d,%d)\n", br.x, br.y, br.width, br.height );
    }

    // STEP 5: construct image to display contours, bounding rectangles and origins of rectangles
    cv::Mat img_contours = cv::Mat::zeros( img.size(), CV_8UC3 );
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
    if( contourcount == 2 )
    {
      int peg_x = ( min_x + max_x ) / 2;
      int peg_y = ( min_y + max_y ) / 2;
      printf( "INFO: ESTIMATED PEG POSITION: (x,y)\n" );
      printf( "(%d,%d)\n", peg_x, peg_y );
      Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
      Point peg;
      peg.x = peg_x;
      peg.y = peg_y;
      cv::circle( img_contours, peg, 10, color, 2, 8 );
    }
    else
    {
      printf( "INFO: UNABLE TO ESTIMATE PEG POSITION\n" );
    }
    printf( "---\n" );
    

    // STEP 6: display images
    cv::imshow("img", img);
    cv::imshow("hsv threshold", *img_hsvthreshold);
    cv::imshow("blur", *img_blur);
    cv::imshow( "img_contours", img_contours );

    // STEP 7: check for user request to terminate
    char c = cv::waitKey(30);
    if ( c == ' ' )
      break;

  }

}

