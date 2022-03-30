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


RobotContainer::RobotContainer() {
  _subDriveBase.SetDefaultCommand(CmdJoystickDrive(&_subDriveBase, &_joystick0));
  // Configure the button bindings
  ConfigureButtonBindings();
}

void RobotContainer::ConfigureButtonBindings() {
  frc2::JoystickButton btnShoot{&_joystick0, frc::XboxController::Button::kLeftBumper };
  btnShoot.ToggleWhenPressed(&_cmdShootSequence);
  frc2::JoystickButton IntakeButton{ &_joystick0,frc::XboxController::Button::kRightBumper };
  IntakeButton.WhileHeld(_cmdIntake);
  frc2::JoystickButton OuttakeButton{ &_joystick0,frc::XboxController::Axis::kRightTrigger };
  OuttakeButton.WhileHeld(_cmdOuttake);
  frc2::JoystickButton OuttakeStorageButton{ &_joystick0,frc::XboxController::Axis::kLeftTrigger };
  OuttakeStorageButton.WhileHeld(_cmdOuttake);
  frc2::JoystickButton DeployIntakeButton{ &_joystick0,frc::XboxController::Button::kA};
  DeployIntakeButton.ToggleWhenPressed(_cmdDeployIntake);

  frc2::JoystickButton TrackTargetButton{&_joystick0, frc::XboxController::Button::kX};
  TrackTargetButton.WhileHeld(frc2::ParallelCommandGroup(_cmdTrackTarget, _cmdShooter));

  frc2::JoystickButton StorageButton{ &_joystick0,frc::XboxController::Button::kStart};
  //StorageButton.WhenHeld( _cmdStorageIn );

  // wrapping shootSequence in an instant command because it doesnt have a copy constructor,
  // which is needed for binding to a button
  StorageButton.WhenHeld(frc2::InstantCommand{[this]{_cmdShootSequence.Schedule();}});

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
  return &_cmd2BallAuto;
}
