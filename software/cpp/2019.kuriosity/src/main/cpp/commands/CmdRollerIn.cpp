/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdRollerIn.h"
#include "Robot.h"

CmdRollerIn::CmdRollerIn() {
  Requires(Robot::subRollerIntake.get());
  Requires(Robot::subIntakeOutake.get());
  Requires(Robot::subPanelAffector.get());
}

void CmdRollerIn::Initialize() {}

void CmdRollerIn::Execute() {
  Robot::subRollerIntake->RollerIn();
  Robot::subIntakeOutake->Intake();
  Robot::subPanelAffector->DeployFingers();
  cout << "RollerIn Exe" << endl;
}

// Make this return true when this Command no longer needs to run execute()
bool CmdRollerIn::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdRollerIn::End() {
  Robot::subRollerIntake->Stop();
  Robot::subIntakeOutake->Stop();
  Robot::subPanelAffector->RetractFingers();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdRollerIn::Interrupted() {End();}
