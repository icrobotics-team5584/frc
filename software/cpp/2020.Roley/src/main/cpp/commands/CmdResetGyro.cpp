/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdResetGyro.h"
#include "Robot.h"
#include "subsystems/SubDriveBase.h"

CmdResetGyro::CmdResetGyro() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  std::cout << "reset yaw construct" << std::endl;

}

// Called just before this Command runs the first time
void CmdResetGyro::Initialize() {
  std::cout << "reset yaw start init" << std::endl;
}

// Called repeatedly when this Command is scheduled to run
void CmdResetGyro::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool CmdResetGyro::IsFinished() {
  return !Robot::subDriveBase->isNavxCal();
}

// Called once after isFinished returns true
void CmdResetGyro::End() {
  std::cout << "reset yaw" << std::endl;
  Robot::subDriveBase->resetYaw();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdResetGyro::Interrupted() {
  End();
}
