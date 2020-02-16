/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdElevatorPowerDown.h"

#include "Robot.h"

CmdElevatorPowerDown::CmdElevatorPowerDown() {
  // Use Requires() here to declare subsystem dependencies
  Requires(Robot::subClimber.get());
}

// Called just before this Command runs the first time
void CmdElevatorPowerDown::Initialize() {
  Robot::subClimber->DisablePID();
  Robot::subClimber->setSpeed(-0.1);
}

// Called repeatedly when this Command is scheduled to run
void CmdElevatorPowerDown::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool CmdElevatorPowerDown::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdElevatorPowerDown::End() {
  Robot::subClimber->Stop();
  Robot::subClimber->ElevaterExtendMin();
  Robot::subClimber->EnablePID();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdElevatorPowerDown::Interrupted() {
  End();
}
