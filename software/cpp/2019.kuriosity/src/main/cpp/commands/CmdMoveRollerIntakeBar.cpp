/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdMoveRollerIntakeBar.h"
#include "Robot.h"

CmdMoveRollerIntakeBar::CmdMoveRollerIntakeBar(RollerPosition rollerPosition) {
  // Use Requires() here to declare subsystem dependencies
  Requires(Robot::subRollerIntakeBar.get());
 
    _rollerPosition = rollerPosition;
 
 std::cout << "move intake bar start" << endl;

  
  
}

// Called just before this Command runs the first time
void CmdMoveRollerIntakeBar::Initialize() {
  std::cout << _rollerPosition << endl;
  Robot::subRollerIntakeBar->SetSetpoint(_rollerPosition);
  Robot::subRollerIntakeBar->SetPIDEnabled(true);
}

// Called repeatedly when this Command is scheduled to run
void CmdMoveRollerIntakeBar::Execute() {
}

// Make this return true when this Command no longer needs to run execute()
bool CmdMoveRollerIntakeBar::IsFinished() { 
  Robot::subRollerIntakeBar->OnTarget();
}

// Called once after isFinished returns true
void CmdMoveRollerIntakeBar::End() {
  std::cout << "move intake bar finished" << endl;
  Robot::subRollerIntakeBar->SetPIDEnabled(false);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdMoveRollerIntakeBar::Interrupted() {}
