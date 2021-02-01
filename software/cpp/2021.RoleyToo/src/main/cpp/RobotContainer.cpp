// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <frc2/command/SequentialCommandGroup.h>

#include "RobotContainer.h"

#include "frc2/command/button/JoystickButton.h"

RobotContainer::RobotContainer() {
  // Initialize all of your commands and subsystems here
  _subDriveBase.SetDefaultCommand(CmdJoystickDrive(&_subDriveBase, &_joystick0));
  // Configure the button bindings
  ConfigureButtonBindings();
}

void RobotContainer::ConfigureButtonBindings() {
  // Configure your button bindings here

  frc2::JoystickButton leftBtn{&_joystick0, buttons::leftBtn};
  frc2::JoystickButton aBtn{&_joystick0, buttons::aBtn};
  frc2::JoystickButton xBtn{&_joystick0, buttons::xBtn};

  leftBtn.WhileHeld(_cmdTrackTarget);
  aBtn.WhileHeld(_cmdDriveStorage);
  xBtn.WhenHeld(frc2::SequentialCommandGroup{_cmdSpinColorWheel, _cmdMoveCenterColor, _cmdSpinToColor}); 
  // We're on a whenpressed, the second command doesnt stop calling execute to move to position 40
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return &_cmdAutoCircle;
}
