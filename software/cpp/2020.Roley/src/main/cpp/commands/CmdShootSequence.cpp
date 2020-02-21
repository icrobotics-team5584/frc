/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdShootSequence.h"
#include "Robot.h"

CmdShootSequence::CmdShootSequence() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void CmdShootSequence::Initialize() {
  //retract storage
  Robot::subStorage->Retract();
  //deploy intake
  Robot::subIntake->Deploy();
  //shooter start
  Robot::subShooter->PowerShoot();
  //storage roll
  Robot::subStorage->Forward();
}

// Called repeatedly when this Command is scheduled to run
void CmdShootSequence::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool CmdShootSequence::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdShootSequence::End() {
  //stop rolling storage
  Robot::subStorage->Stop();
  //retract intake
  Robot::subIntake->Stop();
  //stop shooter
  Robot::subShooter->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdShootSequence::Interrupted() {
  End();
}

