/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdSlowDown.h"
#include "commands/CmdDrive.h"
#include "Robot.h"
#include <iostream>

CmdSlowDown::CmdSlowDown() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::subDrivebase.get());
}

// Called just before this Command runs the first time
void CmdSlowDown::Initialize() {
  std::cout << "Cmd slow down initialized" << std::endl;
  Robot::subDrivebase->drive((Robot::m_oi->GetJoystickY()/2), (-Robot::m_oi->GetJoystickX()/2));
  
  Robot::m_oi->GetRightAsix();
}

// Called repeatedly when this Command is scheduled to run
void CmdSlowDown::Execute() 
{
    x = Robot::m_oi->joystick1->GetX();
  y = Robot::m_oi->joystick1->GetY();
  axis = Robot::m_oi->joystick1->GetRawAxis(triggerR);
  //SmartDashboard::PutNumber("axis test", axis);
  Robot::subDrivebase->drive(y/(axis + 1),(-(x/(axis + 1))));
}

// Make this return true when this Command no longer needs to run execute()
bool CmdSlowDown::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdSlowDown::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdSlowDown::Interrupted() {}
