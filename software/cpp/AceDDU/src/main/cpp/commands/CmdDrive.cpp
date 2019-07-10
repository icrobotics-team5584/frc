/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Robot.h>
#include "commands/CmdDrive.h"
#include <iostream>

CmdDrive::CmdDrive() {
  // Use Requires() here to declare subsystem dependencies
  Requires(Robot::subDrivebase.get());
   
}

// Called just before this Command runs the first time
void CmdDrive::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void CmdDrive::Execute() {
    //Robot::subDrivebase->drive(Robot::m_oi->GetJoystickY(), Robot::m_oi->GetJoystickX());
    //std::cout<<Robot::m_oi->GetJoystickX()<<std::endl;
    //std::cout<<Robot::m_oi->GetJoystickY()<<std::endl;
  
}
  

// Make this return true when this Command no longer needs to run execute()
bool CmdDrive::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdDrive::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdDrive::Interrupted() {}
