/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdArmToFloor.h"

const double CmdArmToFloor::angle = 0;

CmdArmToFloor::CmdArmToFloor() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::subEncodedArm.get());
}

// Called just before this Command runs the first time
void CmdArmToFloor::Initialize() {
  Robot::subEncodedArm->ConfigTalon();
  Robot::subEncodedArm->SetPosition(angle);
  std::cout << "arm to ground start" << std::endl;
}

// Called repeatedly when this Command is scheduled to run
void CmdArmToFloor::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool CmdArmToFloor::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdArmToFloor::End() {
  std::cout << "arm to ground" << std::endl;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdArmToFloor::Interrupted() {
  End();
}
