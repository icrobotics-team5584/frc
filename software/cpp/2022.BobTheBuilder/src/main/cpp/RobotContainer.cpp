// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"
#include "commands/CmdIntake.h"
#include <frc2/command/button/JoystickButton.h>
#include <frc/XboxController.h>
RobotContainer::RobotContainer() {
  _subDriveBase.SetDefaultCommand(CmdJoystickDrive(&_subDriveBase, &_joystick0));
  // Configure the button bindings
  ConfigureButtonBindings();
}

void RobotContainer::ConfigureButtonBindings() {
  frc2::JoystickButton IntakeButton{ &_joystick0,frc::XboxController::Button::kRightBumper };
  IntakeButton.WhileHeld(_cmdIntake);
  frc2::JoystickButton OuttakeButton{ &_joystick0,frc::XboxController::Button::kLeftBumper };
}


frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return NULL;
}
