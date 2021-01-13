// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/cmdDriveNeoNT.h"

#include "frc/smartdashboard/SmartDashboard.h"

cmdDriveNeoNT::cmdDriveNeoNT(subMaxsNeo* SubMaxsNeo) {
  // Use addRequirements() here to declare subsystem dependencies.
  frc::SmartDashboard::PutNumber("TestMotorPercentage", 0);
  AddRequirements(SubMaxsNeo);
  _SubMaxsNeo = SubMaxsNeo;
}

// Called when the command is initially scheduled.
void cmdDriveNeoNT::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void cmdDriveNeoNT::Execute() {
  int percentageSpeed = frc::SmartDashboard::GetNumber("TestMotorPercentage", 0);
  _SubMaxsNeo->driveMaxsNeo(percentageSpeed);
}

// Called once the command ends or is interrupted.
void cmdDriveNeoNT::End(bool interrupted) {}

// Returns true when the command should end.
bool cmdDriveNeoNT::IsFinished() {
  return false;
}
