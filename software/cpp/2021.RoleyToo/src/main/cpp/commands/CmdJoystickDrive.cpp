// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdJoystickDrive.h"

CmdJoystickDrive::CmdJoystickDrive(SubDriveBase* subDriveBase, JoystickScaler* joystick) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(subDriveBase);
  _subDriveBase = subDriveBase;
  _joystick = joystick;
}

// Called repeatedly when this Command is scheduled to run
void CmdJoystickDrive::Execute() {
  double speed = _joystick->GetScaledY(frc::GenericHID::JoystickHand::kRightHand);
  double turning = _joystick->GetScaledX(frc::GenericHID::JoystickHand::kRightHand);
  if (_joystick->GetRawButton(9)) { // left stick button
    speed = speed / 2;
    turning = turning / 2;
  }
  _subDriveBase->drive(speed, turning, false);
}

