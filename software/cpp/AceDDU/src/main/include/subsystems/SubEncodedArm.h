/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Commands/Subsystem.h>
#include "WPILib.h"
#include <ctre/phoenix.h>
#include <SmartDashboard/SmartDashboard.h>
#include <iostream>

class SubEncodedArm : public frc::Subsystem {
 private:
  frc::PIDController* armController;
  armPID* _armOutputPID;

	double EncBack = 2500;
	double EncFront = 440;
	//double PotUp = 1435;
	double totalAngle = 90;
	double PIDp = 0.0007;
	double PIDi = 0.0;
	double PIDd = 0.0;

 public:
  SubEncodedArm();
  void InitDefaultCommand() override;
};
