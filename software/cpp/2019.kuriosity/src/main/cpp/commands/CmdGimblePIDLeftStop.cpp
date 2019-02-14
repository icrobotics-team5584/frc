/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdGimblePIDLeftStop.h"
#include "subsystems/SubGimble.h"

CmdGimblePIDLeftStop::CmdGimblePIDLeftStop() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::subGimble.get());
}

// Called just before this Command runs the first time
void CmdGimblePIDLeftStop::Initialize() {
  if(Robot::subGimble->GetTarget() <=  Robot::subGimble->POTPosition())
  {
    Robot::subGimble->stop(1);
    std::cout << "GIMBLE PID LEFT STOP" << std::endl;
  }else{}
}

// Called repeatedly when this Command is scheduled to run
void CmdGimblePIDLeftStop::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool CmdGimblePIDLeftStop::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdGimblePIDLeftStop::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdGimblePIDLeftStop::Interrupted() {
  End();
}
