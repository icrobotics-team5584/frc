#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "GripPipeline.h"

int main()
{

  cv::Mat img;

  grip::GripPipeline ic_pipeline;

  cv::VideoCapture input(0);

  cv::VideoWriter output1(
    "cv_ij_1.avi",
    CV_FOURCC('X', 'V', 'I', 'D'),
    30,
    cv::Size(input.get(CV_CAP_PROP_FRAME_WIDTH),
             input.get(CV_CAP_PROP_FRAME_HEIGHT)));

  cv::VideoWriter output2(
    "cv_ij_2.avi",
    CV_FOURCC('X', 'V', 'I', 'D'),
    30,
    cv::Size(input.get(CV_CAP_PROP_FRAME_WIDTH),
             input.get(CV_CAP_PROP_FRAME_HEIGHT)));

  for (;;)
  {
    if(!input.read(img))
      break;

    ic_pipeline.setsource0(img);
    ic_pipeline.process(img);
    cv::Mat* img_hsvthreshold = ic_pipeline.gethsvThresholdOutput();
    cv::Mat* img_blur = ic_pipeline.getblurOutput();

    // cv::Sobel(img, dst, CV_8U, 1, 1);
    // output1.write(img);
    // output2.write(dst);
    cv::imshow("img", img);
    // cv::imshow("dst", dst);

    cv::imshow("hsv threshold", *img_hsvthreshold);
    cv::imshow("blur", *img_blur);

    char c = cv::waitKey(30);

    if ( c == ' ' )
      break;
  }

}

