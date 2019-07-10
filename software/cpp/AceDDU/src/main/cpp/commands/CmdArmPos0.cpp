/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/cmdArmPos0.h"

cmdArmPos0::cmdArmPos0() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void cmdArmPos0::Initialize() {
  cmdMoveArm.reset(new CmdMoveArm());
  cmdMoveArm->Start();

  subEncodedArm.reset(new SubEncodedArm());
}

// Called repeatedly when this Command is scheduled to run
void cmdArmPos0::Execute() {
  cmdMoveArm->setAngle(0);
}

// Make this return true when this Command no longer needs to run execute()
bool cmdArmPos0::IsFinished() 
{ 
  if(subEncodedArm->getAngle() == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

// Called once after isFinished returns true
void cmdArmPos0::End() {
  cmdMoveArm->End();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void cmdArmPos0::Interrupted() {}
