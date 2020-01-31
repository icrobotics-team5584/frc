/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdClimberLimitUp.h"
#include "Robot.h"
#include "subsystems/SubClimber.h"


CmdClimberLimitUp::CmdClimberLimitUp() {
  Requires(Robot::subClimber.get());
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void CmdClimberLimitUp::Initialize() {
  cout << "Climber limit Up initialized" << std::endl;
  Robot::subClimber->MoveUp();
}

// Called repeatedly when this Command is scheduled to run
void CmdClimberLimitUp::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool CmdClimberLimitUp::IsFinished() { 
  cout << "Climber limit Up initialized" << std::endl;
  return (Robot::subClimber->LimitClimbUpGet());
}

// Called once after isFinished returns true
void CmdClimberLimitUp::End() {
  Robot::subClimber->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdClimberLimitUp::Interrupted() {
  End();
}
