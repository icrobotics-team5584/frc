// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"
#include "commands/CmdIntake.h"
#include <frc2/command/button/JoystickButton.h>
#include <frc/XboxController.h>
#include <frc2/command/ParallelCommandGroup.h>
#include <frc2/command/StartEndCommand.h>
#include <frc2/command/InstantCommand.h>
#include <frc2/command/button/POVButton.h>
#include "Utilities/AxisButton.h"


RobotContainer::RobotContainer() {
  _subDriveBase.SetDefaultCommand(CmdJoystickDrive(&_subDriveBase, &_joystick0));
  // Configure the button bindings
  ConfigureButtonBindings();
}

void RobotContainer::ConfigureButtonBindings() {
  
  frc2::JoystickButton btnShoot{&_joystick0, frc::XboxController::Button::kLeftBumper };
  btnShoot.WhileHeld(&_cmdShootSequence);
  btnShoot.WhenReleased(&_cmdEndShoot);
  frc2::JoystickButton IntakeButton{ &_joystick0,frc::XboxController::Button::kRightBumper };
  IntakeButton.WhileHeld(_cmdIntake);
  AxisButton OuttakeButton{ &_joystick0,frc::XboxController::Axis::kRightTrigger };
  OuttakeButton.WhileHeld(_cmdOuttake);
  AxisButton OuttakeStorageButton{ &_joystick0,frc::XboxController::Axis::kLeftTrigger };
  OuttakeStorageButton.WhileHeld(_cmdStorageOut);
  frc2::JoystickButton DeployIntakeButton{ &_joystick0,frc::XboxController::Button::kA};
  DeployIntakeButton.ToggleWhenPressed(_cmdDeployIntake);

  frc2::JoystickButton TrackTargetButton{&_joystick0, frc::XboxController::Button::kX};
  TrackTargetButton.WhileHeld(frc2::ParallelCommandGroup(_cmdTrackTarget, _cmdShooter));

  frc2::JoystickButton ShooterLowGoal{&_joystick0, frc::XboxController::Button::kBack};
  ShooterLowGoal.WhileHeld(_cmdToggleShootingPosition);

  frc2::POVButton LowGoalMode{&_joystick0, 180, 0};
  LowGoalMode.WhenPressed(frc2::InstantCommand{[this]{_subShooter.SetLowMode(true);}});

  frc2::POVButton HighGoalMode{&_joystick0, 0,0};
  HighGoalMode.WhenPressed(frc2::InstantCommand{[this]{_subShooter.SetLowMode(false);}});

  frc2::JoystickButton ShooterStop{&_joystick0, frc::XboxController::Button::kStart};
  ShooterStop.WhenPressed(_cmdStopShooter);
  

  
}





frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return &_cmd2BallAuto;
}
