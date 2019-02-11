#pragma once
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <vector>
#include <string>
#include <math.h>

namespace grip {

/**
* Contains details of a line.
*
*/
class Line {
	public:
	double x1, y1, x2, y2;
	/**
	* Creates a line with given (x, y) points 1 and 2.
	*
	* @param x1 x coordinate of one point of the line.
	* @param y1 y coordinate of the same point of line as above.
	* @param x2 x coordinate of other point of the line.
	* @param y2 y coordinate of other point of line. 
	*/
	Line(double x1, double y1, double x2, double y2) {
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;
		}

	/**
	* Calculates the length of the line.
	*
	* @return The point to point length of the line. 
	*/
	double length() {
		return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
	}
	
	/**
	* Calculates the angle between the two points. 
	*
	* @return the angle (in degrees between -180 and 180) between the two points.
	*/
	double angle() {
		return (180*atan2(y2 - y1, x2 - x1)/CV_PI);
	}
};

/**
* GripPipeline class.
* 
* An OpenCV pipeline generated by GRIP.
*/
class GripPipeline {
	private:
		cv::Mat resizeImageOutput;
		cv::Mat rgbThresholdOutput;
		std::vector<Line> findLinesOutput;
		std::vector<Line> filterLinesOutput;
		void resizeImage(cv::Mat &, double , double , int , cv::Mat &);
		void rgbThreshold(cv::Mat &, double [], double [], double [], cv::Mat &);
		void findLines(cv::Mat &, std::vector<Line> &);
		void filterLines(std::vector<Line> &, double , double [], std::vector<Line> &);

	public:
		GripPipeline();
		void Process(cv::Mat& source0);
		cv::Mat* GetResizeImageOutput();
		cv::Mat* GetRgbThresholdOutput();
		std::vector<Line>* GetFindLinesOutput();
		std::vector<Line>* GetFilterLinesOutput();
};

} // end namespace grip
