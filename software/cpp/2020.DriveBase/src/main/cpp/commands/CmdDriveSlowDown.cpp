/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdDriveSlowDown.h"

#include "Robot.h"

CmdDriveSlowDown::CmdDriveSlowDown() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::subDriveBase.get());
}

// Called just before this Command runs the first time
void CmdDriveSlowDown::Initialize() {
  std::cout << "Cmd slow down initialized" << std::endl;
  Robot::subDriveBase->Drive((Robot::m_oi.getJoystickY()/2), (-Robot::m_oi.getJoystickX()/2));
  
}

// Called repeatedly when this Command is scheduled to run
void CmdDriveSlowDown::Execute() {
  x = Robot::m_oi.joystick1->GetX();
  y = Robot::m_oi.joystick1->GetY();
  axis = Robot::m_oi.joystick1->GetRawAxis(triggerR);
  //SmartDashboard::PutNumber("axis test", axis);
  Robot::subDriveBase->Drive(y/(axis + 1),(-(x/(axis + 1))));
}

// Make this return true when this Command no longer needs to run execute()
bool CmdDriveSlowDown::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdDriveSlowDown::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdDriveSlowDown::Interrupted() {}
