#include "GripPipeline.h"

namespace grip {

GripPipeline::GripPipeline() {
}
/**
* Runs an iteration of the pipeline and updates outputs.
*/
void GripPipeline::Process(cv::Mat& source0, cv::Mat& source1){

	//Step HSV_Threshold0:
	//input
	cv::Mat hsvThreshold0Input = source0;
	// JR VALUES: double hsvThreshold0Hue[] = {67.98561151079136, 95.52901023890783};
	// JR VALUES: double hsvThreshold0Saturation[] = {0.0, 255.0};
	// JR VALUES: double hsvThreshold0Value[] = {183.1042962240377, 255.0};
	double hsvThreshold0Hue[] = {48.0, 96.0};
	double hsvThreshold0Saturation[] = {0.0, 255.0};
	double hsvThreshold0Value[] = {64.0, 255.0};
	hsvThreshold(hsvThreshold0Input, hsvThreshold0Hue, hsvThreshold0Saturation, hsvThreshold0Value, this->hsvThreshold0Output);
	//Step Blur0:
	//input
	cv::Mat blur0Input = hsvThreshold0Output;
	BlurType blur0Type = BlurType::GAUSSIAN;
	double blur0Radius = 3.6036036036036014;  // default Double
	blur(blur0Input, blur0Type, blur0Radius, this->blur0Output);
	//Step Find_Contours0:
	//input
	cv::Mat findContours0Input = blur0Output;
	bool findContours0ExternalOnly = false;  // default Boolean
	findContours(findContours0Input, findContours0ExternalOnly, this->findContours0Output);
	//Step Filter_Contours0:
	//input
	std::vector<std::vector<cv::Point> > filterContours0Contours = findContours0Output;
	double filterContours0MinArea = 1000.0;  // default Double
	double filterContours0MinPerimeter = 0.0;  // default Double
	double filterContours0MinWidth = 0.0;  // default Double
	double filterContours0MaxWidth = 1000.0;  // default Double
	double filterContours0MinHeight = 0.0;  // default Double
	double filterContours0MaxHeight = 1000.0;  // default Double
	double filterContours0Solidity[] = {0.0, 100};
	double filterContours0MaxVertices = 1.0E7;  // default Double
	double filterContours0MinVertices = 0.0;  // default Double
	double filterContours0MinRatio = 1.5;  // default Double
	double filterContours0MaxRatio = 3.0;  // default Double
	filterContours(filterContours0Contours, filterContours0MinArea, filterContours0MinPerimeter, filterContours0MinWidth, filterContours0MaxWidth, filterContours0MinHeight, filterContours0MaxHeight, filterContours0Solidity, filterContours0MaxVertices, filterContours0MinVertices, filterContours0MinRatio, filterContours0MaxRatio, this->filterContours0Output);

	//Step HSV_Threshold1:
	//input
	cv::Mat hsvThreshold1Input = source1;
	// JR VALUES: double hsvThreshold1Hue[] = {67.98561151079136, 95.52901023890786};
	// JR VALUES: double hsvThreshold1Saturation[] = {0.0, 255.0};
	// JR VALUES: double hsvThreshold1Value[] = {182.64566313051253, 255.0};
	double hsvThreshold1Hue[] = {48.0, 96.0};
	double hsvThreshold1Saturation[] = {0.0, 255.0};
	double hsvThreshold1Value[] = {64.0, 255.0};
	hsvThreshold(hsvThreshold1Input, hsvThreshold1Hue, hsvThreshold1Saturation, hsvThreshold1Value, this->hsvThreshold1Output);
	//Step Blur1:
	//input
	cv::Mat blur1Input = hsvThreshold1Output;
	BlurType blur1Type = BlurType::GAUSSIAN;
	double blur1Radius = 3.6036036036036037;  // default Double
	blur(blur1Input, blur1Type, blur1Radius, this->blur1Output);
	//Step Find_Contours1:
	//input
	cv::Mat findContours1Input = blur1Output;
	bool findContours1ExternalOnly = false;  // default Boolean
	findContours(findContours1Input, findContours1ExternalOnly, this->findContours1Output);
	//Step Filter_Contours1:
	//input
	std::vector<std::vector<cv::Point> > filterContours1Contours = findContours1Output;
	double filterContours1MinArea = 1000.0;  // default Double
	double filterContours1MinPerimeter = 0.0;  // default Double
	double filterContours1MinWidth = 0.0;  // default Double
	double filterContours1MaxWidth = 1000.0;  // default Double
	double filterContours1MinHeight = 0.0;  // default Double
	double filterContours1MaxHeight = 1000.0;  // default Double
	double filterContours1Solidity[] = {0, 100};
	double filterContours1MaxVertices = 1000000.0;  // default Double
	double filterContours1MinVertices = 0.0;  // default Double
	double filterContours1MinRatio = 1.5;  // default Double
	double filterContours1MaxRatio = 3.0;  // default Double
	filterContours(filterContours1Contours, filterContours1MinArea, filterContours1MinPerimeter, filterContours1MinWidth, filterContours1MaxWidth, filterContours1MinHeight, filterContours1MaxHeight, filterContours1Solidity, filterContours1MaxVertices, filterContours1MinVertices, filterContours1MinRatio, filterContours1MaxRatio, this->filterContours1Output);
}


/**
 * This method is a generated setter for source0.
 * @param source the Mat to set
 */
void GripPipeline::SetSource0(cv::Mat &source0){
        source0.copyTo(this->source0);
}


/**
 * This method is a generated setter for source0.
 * @param source the Mat to set
 */
void GripPipeline::SetSource1(cv::Mat &source1){
        source1.copyTo(this->source1);
}
/**
 * This method is a generated getter for the output of a HSV_Threshold.
 * @return Mat output from HSV_Threshold.
 */
cv::Mat* GripPipeline::GetHsvThreshold0Output(){
	return &(this->hsvThreshold0Output);
}
/**
 * This method is a generated getter for the output of a Blur.
 * @return Mat output from Blur.
 */
cv::Mat* GripPipeline::GetBlur0Output(){
	return &(this->blur0Output);
}
/**
 * This method is a generated getter for the output of a Find_Contours.
 * @return ContoursReport output from Find_Contours.
 */
std::vector<std::vector<cv::Point> >* GripPipeline::GetFindContours0Output(){
	return &(this->findContours0Output);
}
/**
 * This method is a generated getter for the output of a Filter_Contours.
 * @return ContoursReport output from Filter_Contours.
 */
std::vector<std::vector<cv::Point> >* GripPipeline::GetFilterContours0Output(){
	return &(this->filterContours0Output);
}
/**
 * This method is a generated getter for the output of a HSV_Threshold.
 * @return Mat output from HSV_Threshold.
 */
cv::Mat* GripPipeline::GetHsvThreshold1Output(){
	return &(this->hsvThreshold1Output);
}
/**
 * This method is a generated getter for the output of a Blur.
 * @return Mat output from Blur.
 */
cv::Mat* GripPipeline::GetBlur1Output(){
	return &(this->blur1Output);
}
/**
 * This method is a generated getter for the output of a Find_Contours.
 * @return ContoursReport output from Find_Contours.
 */
std::vector<std::vector<cv::Point> >* GripPipeline::GetFindContours1Output(){
	return &(this->findContours1Output);
}
/**
 * This method is a generated getter for the output of a Filter_Contours.
 * @return ContoursReport output from Filter_Contours.
 */
std::vector<std::vector<cv::Point> >* GripPipeline::GetFilterContours1Output(){
	return &(this->filterContours1Output);
}
	/**
	 * Segment an image based on hue, saturation, and value ranges.
	 *
	 * @param input The image on which to perform the HSL threshold.
	 * @param hue The min and max hue.
	 * @param sat The min and max saturation.
	 * @param val The min and max value.
	 * @param output The image in which to store the output.
	 */
	void GripPipeline::hsvThreshold(cv::Mat &input, double hue[], double sat[], double val[], cv::Mat &out) {
		cv::cvtColor(input, out, cv::COLOR_BGR2HSV);
		cv::inRange(out,cv::Scalar(hue[0], sat[0], val[0]), cv::Scalar(hue[1], sat[1], val[1]), out);
	}

	/**
	 * Softens an image using one of several filters.
	 *
	 * @param input The image on which to perform the blur.
	 * @param type The blurType to perform.
	 * @param doubleRadius The radius for the blur.
	 * @param output The image in which to store the output.
	 */
	void GripPipeline::blur(cv::Mat &input, BlurType &type, double doubleRadius, cv::Mat &output) {
		int radius = (int)(doubleRadius + 0.5);
		int kernelSize;
		switch(type) {
			case BOX:
				kernelSize = 2 * radius + 1;
				cv::blur(input,output,cv::Size(kernelSize, kernelSize));
				break;
			case GAUSSIAN:
				kernelSize = 6 * radius + 1;
				cv::GaussianBlur(input, output, cv::Size(kernelSize, kernelSize), radius);
				break;
			case MEDIAN:
				kernelSize = 2 * radius + 1;
				cv::medianBlur(input, output, kernelSize);
				break;
			case BILATERAL:
				cv::bilateralFilter(input, output, -1, radius, radius);
				break;
        }
	}
	/**
	 * Finds contours in an image.
	 *
	 * @param input The image to find contours in.
	 * @param externalOnly if only external contours are to be found.
	 * @param contours vector of contours to put contours in.
	 */
	void GripPipeline::findContours(cv::Mat &input, bool externalOnly, std::vector<std::vector<cv::Point> > &contours) {
		std::vector<cv::Vec4i> hierarchy;
		contours.clear();
		int mode = externalOnly ? cv::RETR_EXTERNAL : cv::RETR_LIST;
		int method = cv::CHAIN_APPROX_SIMPLE;
		cv::findContours(input, contours, hierarchy, mode, method);
	}


	/**
	 * Filters through contours.
	 * @param inputContours is the input vector of contours.
	 * @param minArea is the minimum area of a contour that will be kept.
	 * @param minPerimeter is the minimum perimeter of a contour that will be kept.
	 * @param minWidth minimum width of a contour.
	 * @param maxWidth maximum width.
	 * @param minHeight minimum height.
	 * @param maxHeight  maximimum height.
	 * @param solidity the minimum and maximum solidity of a contour.
	 * @param minVertexCount minimum vertex Count of the contours.
	 * @param maxVertexCount maximum vertex Count.
	 * @param minRatio minimum ratio of width to height.
	 * @param maxRatio maximum ratio of width to height.
	 * @param output vector of filtered contours.
	 */
	void GripPipeline::filterContours(std::vector<std::vector<cv::Point> > &inputContours, double minArea, double minPerimeter, double minWidth, double maxWidth, double minHeight, double maxHeight, double solidity[], double maxVertexCount, double minVertexCount, double minRatio, double maxRatio, std::vector<std::vector<cv::Point> > &output) {
		std::vector<cv::Point> hull;
		output.clear();
		for (std::vector<cv::Point> contour: inputContours) {
			cv::Rect bb = boundingRect(contour);
			if (bb.width < minWidth || bb.width > maxWidth) continue;
			if (bb.height < minHeight || bb.height > maxHeight) continue;
			double area = cv::contourArea(contour);
			if (area < minArea) continue;
			if (arcLength(contour, true) < minPerimeter) continue;
			cv::convexHull(cv::Mat(contour, true), hull);
			double solid = 100 * area / cv::contourArea(hull);
			if (solid < solidity[0] || solid > solidity[1]) continue;
			if (contour.size() < minVertexCount || contour.size() > maxVertexCount)	continue;
			double ratio = (double) bb.width / (double) bb.height;
			if (ratio < minRatio || ratio > maxRatio) continue;
			output.push_back(contour);
		}
	}



} // end grip namespace

