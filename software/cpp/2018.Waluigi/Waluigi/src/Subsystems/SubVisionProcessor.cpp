/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "SubVisionProcessor.h"
#include "../Robot.h"
#include "../RobotMap.h"
#include <CameraServer.h>

SubVisionProcessor::SubVisionProcessor() : Subsystem("SubVisionProcessor") {

	_visionThreadPtr = new std::thread(SubVisionProcessor::VisionThread);
    _visionThreadPtr->detach();
}

void SubVisionProcessor::VisionThread()
{
	cs::UsbCamera camera = CameraServer::GetInstance()->StartAutomaticCapture();
	camera.SetResolution(xRes, yRes);
	cs::CvSink cvSink = CameraServer::GetInstance()->GetVideo();
	cs::CvSource outputStreamStd = CameraServer::GetInstance()->PutVideo("Cyclops", xRes, yRes);
	cv::Mat source;
	cv::Mat output;
	while(true) {
		cvSink.GrabFrame(source);
		FlipCode flipcode = BOTH_AXES;
		cv::flip(source, output, flipcode);
		if( Robot::subEncodedArm->GetArmAngle() > 0 ) {
			outputStreamStd.PutFrame(source);
		} else {
			outputStreamStd.PutFrame(output);
		}
	}
}

void SubVisionProcessor::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}
