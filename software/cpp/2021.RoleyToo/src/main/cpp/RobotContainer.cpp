// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <frc2/command/SequentialCommandGroup.h>

#include "RobotContainer.h"
#include "Utilities/AxisButton.h"
#include "Utilities/POVButton.h"

#include <frc2/command/button/JoystickButton.h>
#include <frc2/command/PrintCommand.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/ParallelCommandGroup.h>

RobotContainer::RobotContainer() {
  // Initialize all of your commands and subsystems here
  _subDriveBase.SetDefaultCommand(CmdJoystickDrive(&_subDriveBase, &_joystick0));
  _subStorage.SetDefaultCommand(CmdIndexStorage(&_subStorage));
  // Configure the button bindings
  ConfigureButtonBindings();

}

void RobotContainer::ConfigureButtonBindings() {
  // Configure your button bindings here
  AxisButton btnTrackTarget{&_joystick0, buttons::leftTrigger};
  AxisButton btnShoot{&_joystick0, buttons::rightTrigger};
  frc2::JoystickButton btnDeployIntake{&_joystick0, buttons::yBtn};
  frc2::JoystickButton btnSpinIntake{&_joystick0, buttons::leftBtn};

  btnDeployIntake.ToggleWhenPressed(_cmdDeployIntake);
  btnSpinIntake.WhileHeld(_cmdIntake);
  btnTrackTarget.WhileHeld(frc2::ParallelCommandGroup{_cmdTrackTarget, _cmdShoot, _cmdMoveStorage});
  btnShoot.WhileHeld(_cmdMoveFeeder);

  //TODO: Intake Toggle Up/Down (Right Trigger)
  //TODO: Color Wheel (B)
  //TODO: Climber on UP DPAD Push
  //TODO: Start: Deploy Climber - Down
  //TODO: Back: Deploy Climber - Up
  //TODO: Shoot Override (X)
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return &_cmdAutoCircle;
}
