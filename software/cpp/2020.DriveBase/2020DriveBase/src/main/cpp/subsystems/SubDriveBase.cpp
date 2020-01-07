/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SubDriveBase.h"
#include "Robot.h"

SubDriveBase::SubDriveBase() : Subsystem("SubDriveBase") {
  _srxFrontLeft = Robot::robotMap.srxDriveBaseFrontLeft;
  _srxFrontRight = Robot::robotMap.srxDriveBaseFrontRight;
  _srxBackLeft = Robot::robotMap.srxDriveBaseBackLeft;
  _srxBackRight = Robot::robotMap.srxDriveBaseBackRight;

}

void SubDriveBase::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

void SubDriveBase::Drive(double speed, double rotation) {
  //This is here at the moment only to allow for a successful compilation.
  _srxFrontLeft->Set(ControlMode::PercentOutput, 0);
  _srxFrontRight->Set(ControlMode::PercentOutput, 0);  
  _srxBackLeft->Set(ControlMode::PercentOutput, 0);
  _srxBackRight->Set(ControlMode::PercentOutput, 0);
  
}
