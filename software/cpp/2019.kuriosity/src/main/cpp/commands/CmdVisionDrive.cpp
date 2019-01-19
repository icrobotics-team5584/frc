/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdVisionDrive.h"
#include "Robot.h"
#include "frc/WPILib.h"
#include <iostream>

CmdVisionDrive::CmdVisionDrive() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::subDriveBase.get());
}

// Called just before this Command runs the first time
void CmdVisionDrive::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void CmdVisionDrive::Execute() {
  //Set direction and power
  double direction = Robot::subDriveBase->getTgtY(); 
  double power = 0.5;
  //Invert for backwards driving
  power *= -1;
  direction *= -1;
  cout << "CmdVisionDrive: power: " << power << endl;
  cout << "CmdVisionDrive: direction: " << direction << endl;
  //Drive
	Robot::subDriveBase->drive(power, direction);
}

// Make this return true when this Command no longer needs to run execute()
bool CmdVisionDrive::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdVisionDrive::End() {
  Robot::subDriveBase->stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdVisionDrive::Interrupted() {End();}
