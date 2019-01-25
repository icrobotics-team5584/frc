#include "GripPipeline.h"

namespace grip {

GripPipeline::GripPipeline() {
	this->switch0Switch = true;
	this->switch1Switch = true;
	this->switch2Switch = true;
	this->switch3Switch = true;
}
/**
* Runs an iteration of the pipeline and updates outputs.
*/
void GripPipeline::Process(cv::Mat& source0, cv::Mat& source1, cv::Mat& source2, cv::Mat& source3){
	//Step RGB_Threshold0:
	//input
	cv::Mat rgbThreshold0Input = source0;
	double rgbThreshold0Red[] = {176.57374100719423, 255.0};
	double rgbThreshold0Green[] = {0.0, 139.0909090909091};
	double rgbThreshold0Blue[] = {0.0, 108.19505766779689};
	rgbThreshold(rgbThreshold0Input, rgbThreshold0Red, rgbThreshold0Green, rgbThreshold0Blue, this->rgbThreshold0Output);
	//Step RGB_Threshold1:
	//input
	cv::Mat rgbThreshold1Input = source1;
	double rgbThreshold1Red[] = {176.57374100719423, 255.0};
	double rgbThreshold1Green[] = {0.0, 128.80546075085323};
	double rgbThreshold1Blue[] = {0.0, 107.04778156996588};
	rgbThreshold(rgbThreshold1Input, rgbThreshold1Red, rgbThreshold1Green, rgbThreshold1Blue, this->rgbThreshold1Output);
	//Step HSV_Threshold0:
	//input
	cv::Mat hsvThreshold0Input = source2;
	double hsvThreshold0Hue[] = {46.94244604316547, 95.52901023890786};
	double hsvThreshold0Saturation[] = {0.0, 255.0};
	double hsvThreshold0Value[] = {64.20863309352518, 255.0};
	hsvThreshold(hsvThreshold0Input, hsvThreshold0Hue, hsvThreshold0Saturation, hsvThreshold0Value, this->hsvThreshold0Output);
	//Step HSV_Threshold1:
	//input
	cv::Mat hsvThreshold1Input = source3;
	double hsvThreshold1Hue[] = {46.94244604316547, 95.52901023890786};
	double hsvThreshold1Saturation[] = {0.0, 255.0};
	double hsvThreshold1Value[] = {61.915467625899275, 255.0};
	hsvThreshold(hsvThreshold1Input, hsvThreshold1Hue, hsvThreshold1Saturation, hsvThreshold1Value, this->hsvThreshold1Output);
	//Step Switch0:
	//input
	bool switch0Switch = this->switch0Switch;
	cv::Mat switch0IfTrue = rgbThreshold0Output;
	cv::Mat switch0IfFalse = hsvThreshold0Output;
	pipelineswitch(switch0Switch, switch0IfTrue, switch0IfFalse, this->switch0Output);
	//Step Switch1:
	//input
	bool switch1Switch = this->switch1Switch;
	cv::Mat switch1IfTrue = rgbThreshold1Output;
	cv::Mat switch1IfFalse = hsvThreshold1Output;
	pipelineswitch(switch1Switch, switch1IfTrue, switch1IfFalse, this->switch1Output);
	//Step Blur0:
	//input
	cv::Mat blur0Input = switch0Output;
	BlurType blur0Type = GAUSSIAN;;
	double blur0Radius = 3.773584905660378;  // default Double
	blur(blur0Input, blur0Type, blur0Radius, this->blur0Output);
	//Step Blur1:
	//input
	cv::Mat blur1Input = switch1Output;
	BlurType blur1Type = GAUSSIAN;;
	double blur1Radius = 3.773584905660378;  // default Double
	blur(blur1Input, blur1Type, blur1Radius, this->blur1Output);
	//Step Find_Contours0:
	//input
	cv::Mat findContours0Input = blur0Output;
	bool findContours0ExternalOnly = false;  // default Boolean
	findContours(findContours0Input, findContours0ExternalOnly, this->findContours0Output);
	//Step Find_Contours1:
	//input
	cv::Mat findContours1Input = blur1Output;
	bool findContours1ExternalOnly = false;  // default Boolean
	findContours(findContours1Input, findContours1ExternalOnly, this->findContours1Output);
	//Step Filter_Contours0:
	//input
	std::vector<std::vector<cv::Point> > filterContours0Contours = findContours1Output;
	double filterContours0MinArea = 1000.0;  // default Double
	double filterContours0MinPerimeter = 0.0;  // default Double
	double filterContours0MinWidth = 0.0;  // default Double
	double filterContours0MaxWidth = 1000.0;  // default Double
	double filterContours0MinHeight = 0.0;  // default Double
	double filterContours0MaxHeight = 1000.0;  // default Double
	double filterContours0Solidity[] = {0, 100};
	double filterContours0MaxVertices = 1000000.0;  // default Double
	double filterContours0MinVertices = 0.0;  // default Double
	double filterContours0MinRatio = 1.5;  // default Double
	double filterContours0MaxRatio = 3.0;  // default Double
	filterContours(filterContours0Contours, filterContours0MinArea, filterContours0MinPerimeter, filterContours0MinWidth, filterContours0MaxWidth, filterContours0MinHeight, filterContours0MaxHeight, filterContours0Solidity, filterContours0MaxVertices, filterContours0MinVertices, filterContours0MinRatio, filterContours0MaxRatio, this->filterContours0Output);
	//Step Filter_Contours1:
	//input
	std::vector<std::vector<cv::Point> > filterContours1Contours = findContours1Output;
	double filterContours1MinArea = 1000.0;  // default Double
	double filterContours1MinPerimeter = 0.0;  // default Double
	double filterContours1MinWidth = 0.0;  // default Double
	double filterContours1MaxWidth = 1000.0;  // default Double
	double filterContours1MinHeight = 0.0;  // default Double
	double filterContours1MaxHeight = 1000.0;  // default Double
	double filterContours1Solidity[] = {92.27871939736346, 100};
	double filterContours1MaxVertices = 1000000.0;  // default Double
	double filterContours1MinVertices = 0.0;  // default Double
	double filterContours1MinRatio = 0.0;  // default Double
	double filterContours1MaxRatio = 1.1;  // default Double
	filterContours(filterContours1Contours, filterContours1MinArea, filterContours1MinPerimeter, filterContours1MinWidth, filterContours1MaxWidth, filterContours1MinHeight, filterContours1MaxHeight, filterContours1Solidity, filterContours1MaxVertices, filterContours1MinVertices, filterContours1MinRatio, filterContours1MaxRatio, this->filterContours1Output);
	//Step Filter_Contours2:
	//input
	std::vector<std::vector<cv::Point> > filterContours2Contours = findContours0Output;
	double filterContours2MinArea = 1000.0;  // default Double
	double filterContours2MinPerimeter = 0.0;  // default Double
	double filterContours2MinWidth = 0.0;  // default Double
	double filterContours2MaxWidth = 1000.0;  // default Double
	double filterContours2MinHeight = 0.0;  // default Double
	double filterContours2MaxHeight = 1000.0;  // default Double
	double filterContours2Solidity[] = {0, 100};
	double filterContours2MaxVertices = 1000000.0;  // default Double
	double filterContours2MinVertices = 0.0;  // default Double
	double filterContours2MinRatio = 1.5;  // default Double
	double filterContours2MaxRatio = 3.0;  // default Double
	filterContours(filterContours2Contours, filterContours2MinArea, filterContours2MinPerimeter, filterContours2MinWidth, filterContours2MaxWidth, filterContours2MinHeight, filterContours2MaxHeight, filterContours2Solidity, filterContours2MaxVertices, filterContours2MinVertices, filterContours2MinRatio, filterContours2MaxRatio, this->filterContours2Output);
	//Step Filter_Contours3:
	//input
	std::vector<std::vector<cv::Point> > filterContours3Contours = findContours0Output;
	double filterContours3MinArea = 1000.0;  // default Double
	double filterContours3MinPerimeter = 0.0;  // default Double
	double filterContours3MinWidth = 0.0;  // default Double
	double filterContours3MaxWidth = 1000.0;  // default Double
	double filterContours3MinHeight = 0.0;  // default Double
	double filterContours3MaxHeight = 1000.0;  // default Double
	double filterContours3Solidity[] = {92.2661870503597, 100};
	double filterContours3MaxVertices = 1000000.0;  // default Double
	double filterContours3MinVertices = 0.0;  // default Double
	double filterContours3MinRatio = 0.0;  // default Double
	double filterContours3MaxRatio = 1.1;  // default Double
	filterContours(filterContours3Contours, filterContours3MinArea, filterContours3MinPerimeter, filterContours3MinWidth, filterContours3MaxWidth, filterContours3MinHeight, filterContours3MaxHeight, filterContours3Solidity, filterContours3MaxVertices, filterContours3MinVertices, filterContours3MinRatio, filterContours3MaxRatio, this->filterContours3Output);
	//Step Switch2:
	//input
	bool switch2Switch = this->switch2Switch;
	std::vector<std::vector<cv::Point> > switch2IfTrue = filterContours1Output;
	std::vector<std::vector<cv::Point> > switch2IfFalse = filterContours2Output;
	pipelineswitch(switch2Switch, switch2IfTrue, switch2IfFalse, this->switch2Output);
	//Step Switch3:
	//input
	bool switch3Switch = this->switch3Switch;
	std::vector<std::vector<cv::Point> > switch3IfTrue = filterContours3Output;
	std::vector<std::vector<cv::Point> > switch3IfFalse = filterContours0Output;
	pipelineswitch(switch3Switch, switch3IfTrue, switch3IfFalse, this->switch3Output);
}

/**
 * This method is a generated setter for source0.
 * @param source the Mat to set
 */
void GripPipeline::SetSource0(cv::Mat &source0){
        source0.copyTo(this->source0);
}

/**
 * This method is a generated setter for source1.
 * @param source the Mat to set
 */
void GripPipeline::SetSource1(cv::Mat &source1){
        source1.copyTo(this->source1);
}

/**
 * This method is a generated setter for source2.
 * @param source the Mat to set
 */
void GripPipeline::SetSource2(cv::Mat &source2){
        source2.copyTo(this->source2);
}

/**
 * This method is a generated setter for source3.
 * @param source the Mat to set
 */
void GripPipeline::SetSource3(cv::Mat &source3){
        source3.copyTo(this->source3);
}

/**
 * This method is a generated setter for the condition of Switch 0
 * @param the condition to set
 */
void GripPipeline::setSwitch0(bool value){
	switch0Switch = value;
}
/**
 * This method is a generated setter for the condition of Switch 1
 * @param the condition to set
 */
void GripPipeline::setSwitch1(bool value){
	switch1Switch = value;
}
/**
 * This method is a generated setter for the condition of Switch 2
 * @param the condition to set
 */
void GripPipeline::setSwitch2(bool value){
	switch2Switch = value;
}
/**
 * This method is a generated setter for the condition of Switch 3
 * @param the condition to set
 */
void GripPipeline::setSwitch3(bool value){
	switch3Switch = value;
}
/**
 * This method is a generated getter for the output of a RGB_Threshold.
 * @return Mat output from RGB_Threshold.
 */
cv::Mat* GripPipeline::GetRgbThreshold0Output(){
	return &(this->rgbThreshold0Output);
}
/**
 * This method is a generated getter for the output of a RGB_Threshold.
 * @return Mat output from RGB_Threshold.
 */
cv::Mat* GripPipeline::GetRgbThreshold1Output(){
	return &(this->rgbThreshold1Output);
}
/**
 * This method is a generated getter for the output of a HSV_Threshold.
 * @return Mat output from HSV_Threshold.
 */
cv::Mat* GripPipeline::GetHsvThreshold0Output(){
	return &(this->hsvThreshold0Output);
}
/**
 * This method is a generated getter for the output of a HSV_Threshold.
 * @return Mat output from HSV_Threshold.
 */
cv::Mat* GripPipeline::GetHsvThreshold1Output(){
	return &(this->hsvThreshold1Output);
}
/**
 * This method is a generated getter for the output of a Switch.
 * @return Mat output from Switch.
 */
cv::Mat* GripPipeline::GetSwitch0Output(){
	return &(this->switch0Output);
}
/**
 * This method is a generated getter for the output of a Switch.
 * @return Mat output from Switch.
 */
cv::Mat* GripPipeline::GetSwitch1Output(){
	return &(this->switch1Output);
}
/**
 * This method is a generated getter for the output of a Blur.
 * @return Mat output from Blur.
 */
cv::Mat* GripPipeline::GetBlur0Output(){
	return &(this->blur0Output);
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
std::vector<std::vector<cv::Point> >* GripPipeline::GetFindContours0Output(){
	return &(this->findContours0Output);
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
std::vector<std::vector<cv::Point> >* GripPipeline::GetFilterContours0Output(){
	return &(this->filterContours0Output);
}
/**
 * This method is a generated getter for the output of a Filter_Contours.
 * @return ContoursReport output from Filter_Contours.
 */
std::vector<std::vector<cv::Point> >* GripPipeline::GetFilterContours1Output(){
	return &(this->filterContours1Output);
}
/**
 * This method is a generated getter for the output of a Filter_Contours.
 * @return ContoursReport output from Filter_Contours.
 */
std::vector<std::vector<cv::Point> >* GripPipeline::GetFilterContours2Output(){
	return &(this->filterContours2Output);
}
/**
 * This method is a generated getter for the output of a Filter_Contours.
 * @return ContoursReport output from Filter_Contours.
 */
std::vector<std::vector<cv::Point> >* GripPipeline::GetFilterContours3Output(){
	return &(this->filterContours3Output);
}
/**
 * This method is a generated getter for the output of a Switch.
 * @return ContoursReport output from Switch.
 */
std::vector<std::vector<cv::Point> >* GripPipeline::GetSwitch2Output(){
	return &(this->switch2Output);
}
/**
 * This method is a generated getter for the output of a Switch.
 * @return ContoursReport output from Switch.
 */
std::vector<std::vector<cv::Point> >* GripPipeline::GetSwitch3Output(){
	return &(this->switch3Output);
}
	/**
	 * Segment an image based on color ranges.
	 *
	 * @param input The image on which to perform the RGB threshold.
	 * @param red The min and max red.
	 * @param green The min and max green.
	 * @param blue The min and max blue.
	 * @param output The image in which to store the output.
	 */
	void GripPipeline::rgbThreshold(cv::Mat &input, double red[], double green[], double blue[], cv::Mat &output) {
		cv::cvtColor(input, output, cv::COLOR_BGR2RGB);
		cv::inRange(output, cv::Scalar(red[0], green[0], blue[0]), cv::Scalar(red[1], green[1], blue[1]), output);
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

	/**
	 * Selects an output from two inputs based on a boolean.
	 *
	 * @param sw The boolean that determines the output.
	 * @param onTrue The output if sw is true.
	 * @param onFalse The output if sw is false.
	 * @param output The output which is equal to either onTrue or onFalse.
	 */
	template<typename T>
	void GripPipeline::pipelineswitch(bool sw, T &onTrue, T &onFalse, T &output) {
		if (sw) {
			output = onTrue;
		}
		else {
			output = onFalse;
		}
	}



} // end grip namespace

