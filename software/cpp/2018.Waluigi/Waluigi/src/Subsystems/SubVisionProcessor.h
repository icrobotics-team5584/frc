/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Commands/Subsystem.h>
#include <WPILib.h>
#include <cscore_oo.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

enum FlipCode {
	X_AXIS = 0,
	Y_AXIS = 1,
	BOTH_AXES = -1,
};

const int xRes = 320;
const int yRes = 240;

class SubVisionProcessor : public frc::Subsystem {
private:
	// cs::VideoSink server;
	// cs::UsbCamera camera;
	std::thread * _visionThreadPtr;
	static void VisionThread();

public:
	SubVisionProcessor();
	void InitDefaultCommand() override;
};
