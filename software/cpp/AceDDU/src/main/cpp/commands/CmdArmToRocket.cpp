/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdArmToRocket.h"

const double CmdArmToRocket::angle = 80;

CmdArmToRocket::CmdArmToRocket()
{
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::subEncodedArm.get());
}

// Called just before this Command runs the first time
void CmdArmToRocket::Initialize() {
  Robot::subEncodedArm->ConfigTalon();
  Robot::subEncodedArm->SetPosition(angle);
  std::cout << "arm to Rocket start" << std::endl;
}

// Called repeatedly when this Command is scheduled to run
void CmdArmToRocket::Execute(){
}

// Make this return true when this Command no longer needs to run execute()
bool CmdArmToRocket::IsFinished(){
  if (Robot::subEncodedArm->IsOnTarget()){
    return true;
  }else{
    return false;
  }
}

// Called once after isFinished returns true
void CmdArmToRocket::End() {
  std::cout << "arm to Rocket end" << std::endl;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdArmToRocket::Interrupted()
{
  End();
}
