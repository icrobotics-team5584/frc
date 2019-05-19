/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdIntakeOutakeIn.h"
#include "Robot.h"

CmdIntakeOutakeIn::CmdIntakeOutakeIn() {
  // Use Requires() here to declare subsystem dependencies
  Requires(Robot::subIntakeOutake.get());
  // Requires(Robot::subRollerIntake.get());
  Requires(Robot::subPanelAffector.get());
}

// Called just before this Command runs the first time
void CmdIntakeOutakeIn::Initialize() {
  //frc::SmartDashboard::PutBoolean("running intake", true);
  Robot::subIntakeOutake->Intake();
  // Robot::subRollerIntake->RollerIn();
  Robot::subPanelAffector->DeployFingers(); // Turns out this makes it easier for the ball to enter
}

// Called repeatedly when this Command is scheduled to run
void CmdIntakeOutakeIn::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool CmdIntakeOutakeIn::IsFinished() { 
  return false; //Robot::subIntakeOutake->GetCargoLimitSwitch(); //or !Robot::_oi->btnIntakeOut->Get(); 
}

// Called once after isFinished returns true
void CmdIntakeOutakeIn::End() {
  //  Robot::subIntakeOutake->Stop();
  //  Robot::subRollerIntake->Stop();
  //  Robot::subPanelAffector->RetractFingers();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdIntakeOutakeIn::Interrupted() {
  End();
}
