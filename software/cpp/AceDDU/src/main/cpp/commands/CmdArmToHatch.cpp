/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdArmToHatch.h"

const double CmdArmToHatch::angle = 27.5;

CmdArmToHatch::CmdArmToHatch() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::subEncodedArm.get());
}

// Called just before this Command runs the first time
void CmdArmToHatch::Initialize() {
  Robot::subEncodedArm->ConfigTalon();
  Robot::subEncodedArm->SetPosition(angle);
}

// Called repeatedly when this Command is scheduled to run
void CmdArmToHatch::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool CmdArmToHatch::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdArmToHatch::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdArmToHatch::Interrupted() {
}
