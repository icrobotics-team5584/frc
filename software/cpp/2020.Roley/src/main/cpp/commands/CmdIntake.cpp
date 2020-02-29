/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdIntake.h"

CmdIntake::CmdIntake() {
  // Require subsystems so other commands cant use the hardware at the same time
  Requires(Robot::subIntake.get());
  Requires(Robot::subStorage.get());
}

// Called just before this Command runs the first time
void CmdIntake::Initialize() {
  Robot::subIntake->Intake();
  //Robot::subStorage->Forward();
  Robot::subStorage->BottomRollerForward();
  timer.Reset();
  currentState = NORMAL;
}

void CmdIntake::Intake()
{
  if (Robot::subStorage->lbrBottomIsBlocked() && !Robot::subStorage->lbrTopIsBlocked())
  {
    Robot::subStorage->Forward();
  }
  else
  {
    Robot::subStorage->Stop();
  }
  Robot::subStorage->BottomRollerForward();
}

void CmdIntake::Shuffle()
{
  startTime = timer.Get();
  if (startTime < 0.25)
  {
    Robot::subStorage->BottomRollerStop();
    Robot::subStorage->Backward();
  }

  //lastShuffle = timer.Get();

  //Robot::subStorage->Stop();
}
// Called repeatedly when this Command is scheduled to run
void CmdIntake::Execute() {
  switch (currentState){
    case NORMAL:
      Intake();
      if (Robot::subStorage->lbrTopIsBlocked() && Robot::subStorage->lbrStorageHasGap())
      {
        currentState = SHUFFLE;
        timer.Reset();
      }
      break;
    case SHUFFLE:
      Shuffle();
      if (timer.Get() > 0.1)
      {
        currentState = NORMAL;
      }
      break;
  }
}

// Make this return true when this Command no longer needs to run execute()
bool CmdIntake::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdIntake::End() {
  Robot::subIntake->Stop();
  Robot::subStorage->Stop();
  Robot::subStorage->BottomRollerStop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdIntake::Interrupted() {
  End();
}
