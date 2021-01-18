// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"
#include "commands/CmdJoystickDrive.h"

RobotContainer::RobotContainer() {
  // Initialize all of your commands and subsystems here
  _subDriveBase.SetDefaultCommand(CmdJoystickDrive(&_subDriveBase, &_joystick0));
  // Configure the button bindings
  ConfigureButtonBindings();
}

void RobotContainer::ConfigureButtonBindings() {
  // Configure your button bindings here
  btnDeployIntake.WhenPressed([this]{_subIntake.Deploy();});
  btnRetractIntake.WhenPressed([this]{_subIntake.Retract();});
  btnIntake.WhenPressed([this]{_subIntake.Intake();});
  btnOuttake.WhenPressed([this]{_subIntake.Outtake();});  
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return NULL;
}
