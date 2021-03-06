/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdIntakePanel.h"
#include "Robot.h"
#include <frc/WPILib.h>

CmdIntakePanel::CmdIntakePanel() {
  // Use Requires() here to declare subsystem dependencies
  Requires(Robot::subPanelAffector.get());
  Requires(Robot::subIntakeOutake.get());
}

// Called just before this Command runs the first time
void CmdIntakePanel::Initialize() {
  Robot::subPanelAffector->DeployFingers();
  Robot::subIntakeOutake->Intake();
}

// Called repeatedly when this Command is scheduled to run
void CmdIntakePanel::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool CmdIntakePanel::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdIntakePanel::End() {
  Robot::subPanelAffector->RetractFingers();
  Robot::subIntakeOutake->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdIntakePanel::Interrupted() {
  End();
}
