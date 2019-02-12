/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdElevatortoIntakeHeight.h"
#include "Robot.h"
#include <cstdlib>
CmdElevatortoIntakeHeight::CmdElevatortoIntakeHeight() {
  // Use Requires() here to declare subsystem dependencies
  Requires(Robot::subElevator.get());
}

// Called just before this Command runs the first time
void CmdElevatortoIntakeHeight::Initialize() {
  Robot::subElevator->ElevatorToPos(desiredRotations);
}

// Called repeatedly when this Command is scheduled to run
void CmdElevatortoIntakeHeight::Execute() {
}

// Make this return true when this Command no longer needs to run execute()
bool CmdElevatortoIntakeHeight::IsFinished() {
  elevatorPos = Robot::subElevator->GetEncoderPosition();
  tolerance = 650;
  error = desiredRotations * 4096 - std::abs(elevatorPos);
  frc::SmartDashboard::PutNumber("elevator error", error);
  if (error < tolerance and error > -tolerance) {
    return true;
  }
  return false;
}

// Called once after isFinished returns true
void CmdElevatortoIntakeHeight::End() {
  frc::SmartDashboard::PutBoolean("Finished running elevator intake", true);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdElevatortoIntakeHeight::Interrupted() {}
