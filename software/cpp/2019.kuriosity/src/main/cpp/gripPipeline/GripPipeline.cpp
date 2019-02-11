/**
 *  MANUAL EDITS REQUIRED TO GET CODE GENERATED BY GRIP TO COMPILE . . . 
 * (a) copy GripPipeline.cpp to src/main/cpp/gripPipeline folder
 * (b) copy GripPipeline.h to src/main/include/gripPipeline folder
 * (c) add "gripPipeline/" to include line in cpp file
 * (d) add "cv::" prefix to "LSD_REFINE_STD" in cpp file
*/

#include "gripPipeline/GripPipeline.h"

namespace grip {

GripPipeline::GripPipeline() {
}

/**
* Runs an iteration of the pipeline and updates outputs.
*/
void GripPipeline::Process(cv::Mat& source0){

	//Step Resize_Image0:
	//input
	cv::Mat resizeImageInput = source0;
	double resizeImageWidth = 160.0;  // default Double
	double resizeImageHeight = 120.0;  // default Double
	int resizeImageInterpolation = cv::INTER_LINEAR;
	resizeImage(resizeImageInput, resizeImageWidth, resizeImageHeight, resizeImageInterpolation, this->resizeImageOutput);

	//Step RGB_Threshold0:
	//input
	cv::Mat rgbThresholdInput = resizeImageOutput;
	double rgbThresholdRed[] = {0.0, 165.7935153583618};
	double rgbThresholdGreen[] = {0.0, 107.04778156996588};
	double rgbThresholdBlue[] = {0.0, 255.0};
	rgbThreshold(rgbThresholdInput, rgbThresholdRed, rgbThresholdGreen, rgbThresholdBlue, this->rgbThresholdOutput);

	//Step Find_Lines0:
	//input
	cv::Mat findLinesInput = rgbThresholdOutput;
	findLines(findLinesInput, this->findLinesOutput);

	//Step Filter_Lines0:
	//input
	std::vector<Line> filterLinesLines = findLinesOutput;
	double filterLinesMinLength = 50.0;  // default Double
	double filterLinesAngle[] = {142.44604316546764, 209.48805460750853};
	filterLines(filterLinesLines, filterLinesMinLength, filterLinesAngle, this->filterLinesOutput);

}

/**
 * This method is a generated getter for the output of a Resize_Image.
 * @return Mat output from Resize_Image.
 */
cv::Mat* GripPipeline::GetResizeImageOutput(){
	return &(this->resizeImageOutput);
}

/**
 * This method is a generated getter for the output of a RGB_Threshold.
 * @return Mat output from RGB_Threshold.
 */
cv::Mat* GripPipeline::GetRgbThresholdOutput(){
	return &(this->rgbThresholdOutput);
}

/**
 * This method is a generated getter for the output of a Find_Lines.
 * @return LinesReport output from Find_Lines.
 */
std::vector<Line>* GripPipeline::GetFindLinesOutput(){
	return &(this->findLinesOutput);
}

/**
 * This method is a generated getter for the output of a Filter_Lines.
 * @return LinesReport output from Filter_Lines.
 */
std::vector<Line>* GripPipeline::GetFilterLinesOutput(){
	return &(this->filterLinesOutput);
}

/**
 * Scales and image to an exact size.
 *
 * @param input The image on which to perform the Resize.
 * @param width The width of the output in pixels.
 * @param height The height of the output in pixels.
 * @param interpolation The type of interpolation.
 * @param output The image in which to store the output.
 */
void GripPipeline::resizeImage(cv::Mat &input, double width, double height, int interpolation, cv::Mat &output) {
	cv::resize(input, output, cv::Size(width, height), 0.0, 0.0, interpolation);
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
 * Finds all line segments in an image.
 *
 * @param input The image on which to perform the find lines.
 * @param lineList The output where the lines are stored.
 */
void GripPipeline::findLines(cv::Mat &input, std::vector<Line> &lineList) {
	cv::Ptr<cv::LineSegmentDetector> lsd = cv::createLineSegmentDetector(cv::LSD_REFINE_STD);
	std::vector<cv::Vec4i> lines;
	lineList.clear();
	if (input.channels() == 1) {
		lsd->detect(input, lines);
	} else {
		// The line detector works on a single channel.
		cv::Mat tmp;
		cv::cvtColor(input, tmp, cv::COLOR_BGR2GRAY);
		lsd->detect(tmp, lines);
	}
	// Store the lines in the LinesReport object
	if (!lines.empty()) {
		for (int i = 0; i < lines.size(); i++) {
			cv::Vec4i line = lines[i];
			lineList.push_back(Line(line[0], line[1], line[2], line[3]));
		}
	}
}

/**
 * Filters out lines that do not meet certain criteria.
 *
 * @param inputs The lines that will be filtered.
 * @param minLength The minimum length of a line to be kept.
 * @param angle The minimum and maximum angle of a line to be kept.
 * @param outputs The output lines after the filter.
 */

void GripPipeline::filterLines(std::vector<Line> &inputs, double minLength, double angle[], std::vector<Line> &outputs) {
	outputs.clear();
	double LongestLineLength = 0;
	double LongestLineMidX = 0;
	for (Line line: inputs) {
		if (line.length()>abs(minLength)) {
			if ((line.angle() >= angle[0] && line.angle() <= angle[1]) ||
					(line.angle() + 180.0 >= angle[0] && line.angle() + 180.0 <=angle[1])) {
				outputs.push_back(line);
			}	
		}
		double CurrentLineLength = line.length();
		if (CurrentLineLength > LongestLineLength)
		{
			LongestLineLength = CurrentLineLength;
			LongestLineMidX = line.MidX;
		}
	}	
}



} // end grip namespace
