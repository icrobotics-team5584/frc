/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdVacuumReverse.h"
#include "Robot.h"
CmdVacuumReverse::CmdVacuumReverse() {
  // Use Requires() here to declare subsystem dependencies
  std::cout << "CmdVacuum Construct" << std::endl;
  Requires(Robot::subClimber.get());
  std::cout << "CmdVacuum Construct aFTER" << std::endl;

  
}

// Called just before this Command runs the first time
void CmdVacuumReverse::Initialize() {
    std::cout << "CmdVacuum Init" << std::endl;
  Robot::subClimber->VacuumIn();

  //timer.Start();
  //timer.Reset();
}

// Called repeatedly when this Command is scheduled to run
void CmdVacuumReverse::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool CmdVacuumReverse::IsFinished() { 
  //if(timer.Get() > 3){
    //timer.Stop();
    //return true;
  //}else{
    return false; 
  //}
}

// Called once after isFinished returns true
void CmdVacuumReverse::End() {
  Robot::subClimber->VacuumOut();
  std::cout << "CmdVacuum End" << std::endl;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdVacuumReverse::Interrupted() {
  End();
}
