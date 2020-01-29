#include "GripPipeline.h"

namespace grip {

GripPipeline::GripPipeline() {
}
/**
* Runs an iteration of the pipeline and updates outputs.
*/
void GripPipeline::Process(cv::Mat& source0){
	//Step Resize_Image0:
	//Convert CPU cv::Mat to GPU cv::GpuMat here
	cv::cuda::GpuMat source1(source0);
	source1.upload(source0);	

	//input
	cv::cuda::GpuMat resizeImageInput = source1;
	double resizeImageWidth = 320.0;  // default Double
	double resizeImageHeight = 180.0;  // default Double
	int resizeImageInterpolation = cv::INTER_CUBIC;
	resizeImage(resizeImageInput, resizeImageWidth, resizeImageHeight, resizeImageInterpolation, this->resizeImageOutput);
	//Step Blur0:
	//input
	cv::cuda::GpuMat blurInput = resizeImageOutput;
	BlurType blurType = BlurType::GAUSSIAN;
	double blurRadius = 4.118404732094154;  // default Double
	blur(blurInput, blurType, blurRadius, this->blurOutput);


	//Step HSV_Threshold0:
	//input
	cv::Mat hsvThresholdInput;

	blurOutput.download(hsvThresholdInput);



	double hsvThresholdHue[] = {63, 82};
	double hsvThresholdSaturation[] = {195, 255};
	double hsvThresholdValue[] = {38, 127};
	hsvThreshold(hsvThresholdInput, hsvThresholdHue, hsvThresholdSaturation, hsvThresholdValue, this->hsvThresholdOutput);
	//Step Find_Contours0:
	//Convert GPU cv::GpuMat to CPU cv::Mat

	//input
	cv::Mat findContoursInput = hsvThresholdOutput;

	bool findContoursExternalOnly = false;  // default Boolean
	findContours(findContoursInput, findContoursExternalOnly, this->findContoursOutput);
	//Step Filter_Contours0:
	//input
	std::vector<std::vector<cv::Point> > filterContoursContours = findContoursOutput;
	double filterContoursMinArea = 200.0;  // default Double
	double filterContoursMinPerimeter = 0.0;  // default Double
	double filterContoursMinWidth = 0.0;  // default Double
	double filterContoursMaxWidth = 1000.0;  // default Double
	double filterContoursMinHeight = 0.0;  // default Double
	double filterContoursMaxHeight = 1000.0;  // default Double
	double filterContoursSolidity[] = {0, 100};
	double filterContoursMaxVertices = 1000000.0;  // default Double
	double filterContoursMinVertices = 0.0;  // default Double
	double filterContoursMinRatio = 0.0;  // default Double
	double filterContoursMaxRatio = 1000.0;  // default Double
	filterContours(filterContoursContours, filterContoursMinArea, filterContoursMinPerimeter, filterContoursMinWidth, filterContoursMaxWidth, filterContoursMinHeight, filterContoursMaxHeight, filterContoursSolidity, filterContoursMaxVertices, filterContoursMinVertices, filterContoursMinRatio, filterContoursMaxRatio, this->filterContoursOutput);
}

void GripPipeline::setsource0(cv::Mat &source0){
	source0.copyTo(this->source0);
}

/**
 * This method is a generated getter for the output of a Resize_Image.
 * @return Mat output from Resize_Image.
 */
cv::Mat* GripPipeline::GetResizeImageOutput(){
	this->resizeImageOutput.download(tempMat);
	return &(tempMat);
}
/**
 * This method is a generated getter for the output of a Blur.
 * @return Mat output from Blur.
 */
cv::Mat* GripPipeline::GetBlurOutput(){
	this->blurOutput.download(tempMat);
	return &(tempMat);
}
/**
 * This method is a generated getter for the output of a HSV_Threshold.
 * @return Mat output from HSV_Threshold.
 */
cv::Mat* GripPipeline::GetHsvThresholdOutput(){
	//this->hsvThresholdOutput.download(tempMat);
	return &(this->hsvThresholdOutput);
}
/**
 * This method is a generated getter for the output of a Find_Contours.
 * @return ContoursReport output from Find_Contours.
 */
std::vector<std::vector<cv::Point> >* GripPipeline::GetFindContoursOutput(){
	return &(this->findContoursOutput);
}
/**
 * This method is a generated getter for the output of a Filter_Contours.
 * @return ContoursReport output from Filter_Contours.
 */
std::vector<std::vector<cv::Point> >* GripPipeline::GetFilterContoursOutput(){
	return &(this->filterContoursOutput);
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
	void GripPipeline::resizeImage(cv::cuda::GpuMat &input, double width, double height, int interpolation, cv::cuda::GpuMat &output) {
		cv::cuda::resize(input, output, cv::Size(width, height), 0.0, 0.0, interpolation);
	}

	/**
	 * Softens an image using one of several filters.
	 *
	 * @param input The image on which to perform the blur.
	 * @param type The blurType to perform.
	 * @param doubleRadius The radius for the blur.
	 * @param output The image in which to store the output.
	 */
	void GripPipeline::blur(cv::cuda::GpuMat &input, BlurType &type, double doubleRadius, cv::cuda::GpuMat &output) {
		int radius = (int)(doubleRadius + 0.5);
		int kernelSize;
		cv::Ptr<cv::cuda::Filter> filter;
		switch(type) {
			case BOX:
				kernelSize = 2 * radius + 1;
				filter = cv::cuda::createBoxFilter(input.type(), output.type(), cv::Size(kernelSize, kernelSize));
				break;
			case GAUSSIAN:
				kernelSize = 6 * radius + 1;
				filter = cv::cuda::createGaussianFilter(input.type(), output.type(), cv::Size(kernelSize, kernelSize), radius);
				break;
			case MEDIAN:
				kernelSize = 2 * radius + 1;
				filter = cv::cuda::createMedianFilter(input.type(), kernelSize);
				break;
        	}
		filter->apply( input, output );
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
/*		cv::gpu::GpuMat hsv[3];
		cv::gpu::GpuMat hsvL[3];
		cv::gpu::GpuMat hsvU[3];
		cv::gpu::GpuMat hsvOut[3];
		cv::gpu::GpuMat temp;*/

		cv::cvtColor(input, out, cv::COLOR_BGR2HSV);
		cv::inRange(out,cv::Scalar(hue[0], sat[0], val[0]), cv::Scalar(hue[1], sat[1], val[1]), out);
		/*cv::gpu::split(input, hsv);

		cv::gpu::threshold(hsv[0], hsvL[0], hue[0], 255, cv::THRESH_BINARY);
		cv::gpu::threshold(hsv[0], hsvU[0], hue[1], 255, cv::THRESH_BINARY_INV);
		cv::gpu::bitwise_and(hsvL[0], hsvU[0], hsvOut[0]);

		cv::gpu::threshold(hsv[1], hsvL[1], sat[0], 255, cv::THRESH_BINARY);
		cv::gpu::threshold(hsv[1], hsvU[1], sat[1], 255, cv::THRESH_BINARY_INV);
		cv::gpu::bitwise_and(hsvL[1], hsvU[1], hsvOut[1]);

		cv::gpu::threshold(hsv[2], hsvL[2], val[0], 255, cv::THRESH_BINARY);
		cv::gpu::threshold(hsv[2], hsvU[2], val[1], 255, cv::THRESH_BINARY_INV);
		cv::gpu::bitwise_and(hsvL[2], hsvU[2], hsvOut[2]);
*/



		
		//cv::gpu::threshold(shsv[0], thresc[0], hue[0], hue[1], cv::THRESH_BINARY);
		//cv::gpu::threshold(shsv[1], thresc[1], sat[0], sat[1], cv::THRESH_BINARY);
		//cv::gpu::threshold(shsv[2], thresc[2], val[0], val[1], cv::THRESH_BINARY);

		//cv::gpu::bitwise_and(hsvOut[0], hsvOut[1], temp);
		//cv::gpu::bitwise_and(temp, hsvOut[2], out);
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