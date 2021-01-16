// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdJoystickDrive.h"

CmdJoystickDrive::CmdJoystickDrive(SubDriveBase* subDriveBase, frc::Joystick* joystick) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(subDriveBase);
  _subDriveBase = subDriveBase;
  _joystick = joystick;
}

// Called repeatedly when this Command is scheduled to run
void CmdJoystickDrive::Execute() {
  _subDriveBase->drive(_joystick->GetY(), _joystick->GetX(), true);
}

