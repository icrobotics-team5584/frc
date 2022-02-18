// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"
#include "commands/CmdIntake.h"
#include <frc2/command/button/JoystickButton.h>
#include <frc/XboxController.h>
#include <frc2/command/ParallelCommandGroup.h>
#include <frc2/command/StartEndCommand.h>


RobotContainer::RobotContainer() {
  _subDriveBase.SetDefaultCommand(CmdJoystickDrive(&_subDriveBase, &_joystick0));
  // Configure the button bindings
  ConfigureButtonBindings();

  _autoChooser.AddOption("2 Ball", &_cmd2BallAuto);
  _autoChooser.AddOption("5 Ball", &_cmd5BallAuto);
  _autoChooser.AddOption("1 Ball", &_cmd1BallAuto);

  frc::SmartDashboard::PutData("Auto chooser", &_autoChooser);
}

void RobotContainer::ConfigureButtonBindings() {
  frc2::JoystickButton btnShoot{&_joystick0, frc::XboxController::Button::kB };
  btnShoot.ToggleWhenPressed(&_cmdShooter);
  frc2::JoystickButton IntakeButton{ &_joystick0,frc::XboxController::Button::kRightBumper };
  IntakeButton.WhileHeld(_cmdIntake);
  frc2::JoystickButton OuttakeButton{ &_joystick0,frc::XboxController::Button::kLeftBumper };
  OuttakeButton.WhileHeld(_cmdOuttake);
  frc2::JoystickButton DeployIntakeButton{ &_joystick0,frc::XboxController::Button::kA};
  DeployIntakeButton.ToggleWhenPressed(_cmdDeployIntake);

  frc2::JoystickButton TrackTargetButton{&_joystick0, frc::XboxController::Button::kX};
  TrackTargetButton.WhileHeld(frc2::ParallelCommandGroup(_cmdTrackTarget, _cmdShooter));

  frc2::JoystickButton StorageButton{ &_joystick0,frc::XboxController::Button::kStart};
  StorageButton.WhenHeld( _cmdStorageIn );

   frc2::JoystickButton StorageOuttakeButton{ &_joystick0,frc::XboxController::Button::kBack};
  StorageOuttakeButton.WhenHeld(
    frc2::StartEndCommand(
      [this]{_subStorage.Out();},
      [this]{_subStorage.Stop();}
    )
  );
  frc::SmartDashboard::PutData("SpinUpCommand", &_cmdSpinUpShooter);
}





frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  frc2::Command* selected = _autoChooser.GetSelected();
  return selected;
}
