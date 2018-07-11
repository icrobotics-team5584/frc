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

class SubCamera : public frc::Subsystem {
private:
	cs::VideoSink server;
	cs::UsbCamera camera;

public:
	SubCamera();
	void InitDefaultCommand() override;
	void flipImage();
};

