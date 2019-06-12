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
  	
  	//armPID* _armOutputPID;
	std::shared_ptr<WPI_TalonSRX> srxArmFront;
	std::shared_ptr<WPI_TalonSRX> srxArmBack;

	

 public:
  SubEncodedArm();
  void InitDefaultCommand() override;
  int getEncoder();
  void setSpeed(double speed);
};
