// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

#include "frc2/command/button/JoystickButton.h"

RobotContainer::RobotContainer() {
  // Initialize all of your commands and subsystems here
  //_subDriveBase.SetDefaultCommand(CmdJoystickDrive(&_subDriveBase, &_joystick0)); // Change this when migrating from drive base to actual robot.
  // Configure the button bindings
  ConfigureButtonBindings();
}

void RobotContainer::ConfigureButtonBindings() {
  // Configure your button bindings here

  frc2::JoystickButton leftBtn{&_joystick0, buttons::leftBtn};

  leftBtn.WhileHeld(_cmdTrackTarget);
  
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return NULL;
}
