/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdBuddyLock.h"
#include "Robot.h"

CmdBuddyLock::CmdBuddyLock() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::subBuddyClimb.get());
}

// Called just before this Command runs the first time
void CmdBuddyLock::Initialize() {
  double time = Robot::timer->GetMatchTime();
  SmartDashboard::PutNumber("Time Via cmdSOLReverse", time);
  if(Robot::oi->GetOverride()){
    Robot::subBuddyClimb->Reverse();
  }
  if(time > 30){
    SmartDashboard::PutString("Release SOL", "CANNOT RELEASE SOL");
  }
  else{
    Robot::subBuddyClimb->Reverse(); 
  }
}

// Called repeatedly when this Command is scheduled to run
void CmdBuddyLock::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool CmdBuddyLock::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdBuddyLock::End() {
  Robot::subBuddyClimb->Forward();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdBuddyLock::Interrupted() {
  End();
}
