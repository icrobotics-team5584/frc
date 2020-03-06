/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdShuffle.h"
#include "Robot.h"
CmdShuffle::CmdShuffle() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::subStorage.get());
}

// Called just before this Command runs the first time
void CmdShuffle::Initialize() {
  Robot::subStorage->Backward();
  shuffleTimer.Reset();
  shuffleTimer.Start();
}

// Called repeatedly when this Command is scheduled to run
void CmdShuffle::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool CmdShuffle::IsFinished() { 
  if(shuffleTimer.Get() > 0.5){
    return true;
  }else{
    return false; 
  }
}

// Called once after isFinished returns true
void CmdShuffle::End() {
  Robot::subStorage->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdShuffle::Interrupted() {
  End();
}
