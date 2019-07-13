/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdArmBackwards.h"

CmdArmBackwards::CmdArmBackwards() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::subEncodedArm.get());
}

// Called just before this Command runs the first time
void CmdArmBackwards::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void CmdArmBackwards::Execute() {
  double speed = frc::SmartDashboard::GetNumber("Arm Speed", 0);
  Robot::subEncodedArm->setSpeed(-speed);
}

// Make this return true when this Command no longer needs to run execute()
bool CmdArmBackwards::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdArmBackwards::End() {
  Robot::subEncodedArm->setSpeed(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdArmBackwards::Interrupted() {
  End();
}
