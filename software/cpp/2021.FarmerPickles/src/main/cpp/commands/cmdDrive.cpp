// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/cmdDrive.h"

cmdDrive::cmdDrive(subDriveBase* SubDriveBase, frc::Joystick* driverController) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(SubDriveBase);
  
  _driverController = driverController;
  _SubDriveBase = SubDriveBase;
  
}

// Called when the command is initially scheduled.
void cmdDrive::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void cmdDrive::Execute() {
  //(speed, rotation)

  double speed = _driverController->GetX();
  double rot = _driverController->GetY();

  _SubDriveBase->Drive(speed, rot);
}

// Called once the command ends or is interrupted.
void cmdDrive::End(bool interrupted) {}

// Returns true when the command should end.
bool cmdDrive::IsFinished() {
  return false;
}
