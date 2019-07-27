/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdOverride.h"
#include "Robot.h"
CmdOverride::CmdOverride() {
  // Use Requires() here to declare subsystem dependencies
  Requires(Robot::subEncodedArm.get());
}

// Called just before this Command runs the first time
void CmdOverride::Initialize() {
  Robot::subEncodedArm->ConfigTalonOverride();
}

// Called repeatedly when this Command is scheduled to run
void CmdOverride::Execute() {
  Robot::subEncodedArm->setSpeed((Robot::m_oi->GetRightYAxis())/1.5);
}

// Make this return true when this Command no longer needs to run execute()
bool CmdOverride::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdOverride::End() {
    Robot::subEncodedArm->setSpeed(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdOverride::Interrupted() {
  End();
}
