/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SubGimble.h"
#include "Robot.h"

SubGimble::SubGimble() : Subsystem("ExampleSubsystem") {

  _talGimble = Robot::_robotMap->talGimble;
  _anaGimblePot = Robot::_robotMap->subGimblePot;
  _LimitLeft = Robot::_robotMap->subGimbleLimitLeft;  
  _LimitRight = Robot::_robotMap->subGimbleLimitRight;

  _potSourcePID = new PIDPot();

  gimbleController = new PIDController(PIDp, PIDi, PIDd, _potSourcePID, _talGimble.get());
  gimbleController->SetSetpoint(PotCentre);
	gimbleController->SetInputRange(PotLeft, PotRight);
	gimbleController->SetOutputRange(0.5, -0.5);
	gimbleController->SetContinuous(false);
	gimbleController->Disable();
//	frc::SmartDashboard::PutData("Arm PID Controls", armController);  
}

void SubGimble::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void SubGimble::rotateLeft() {
  _talGimble->Set(rotateSpeed);
}
void SubGimble::rotateRight() {
  _talGimble->Set(-rotateSpeed);
}
void SubGimble::stop() {
  _talGimble->Set(0.0);
}