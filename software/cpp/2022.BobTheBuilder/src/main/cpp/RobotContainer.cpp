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

  _autoChooser.AddOption("2 Ball", &_cmd2BallAuto);
  _autoChooser.AddOption("5 Ball", &_cmd5BallAuto);
  _autoChooser.AddOption("1 Ball", &_cmd1BallAuto);
  _autoChooser.AddOption("3 Ball", &_cmd3BallAuto);

  frc::SmartDashboard::PutData("Auto chooser", &_autoChooser);
}

void RobotContainer::ConfigureButtonBindings() {
  typedef frc::XboxController::Button Btn;

  frc2::JoystickButton btnShoot{&_joystick0, frc::XboxController::Button::kLeftBumper };
  btnShoot.WhileHeld(&_cmdShootSequence);
  btnShoot.WhenReleased(&_cmdEndShoot);
  frc2::JoystickButton IntakeButton{ &_joystick0,frc::XboxController::Button::kRightBumper };
  IntakeButton.WhileHeld(_cmdIntake);
  AxisButton OuttakeButton{ &_joystick0,frc::XboxController::Axis::kRightTrigger };
  OuttakeButton.WhileHeld(_cmdOuttake);
  // frc2::JoystickButton DeployIntakeButton{ &_joystick0,frc::XboxController::Button::kA};
  // DeployIntakeButton.ToggleWhenPressed(_cmdDeployIntake);
  AxisButton OuttakeStorageButton{ &_joystick0,frc::XboxController::Axis::kLeftTrigger };
  OuttakeStorageButton.WhileHeld(_cmdStorageOut);

  // frc2::JoystickButton TrackTargetButton{&_joystick0, frc::XboxController::Button::kX};
  // TrackTargetButton.WhileHeld(frc2::ParallelCommandGroup(_cmdTrackTarget, _cmdShooter));

  frc2::JoystickButton{&_joystick0, Btn::kY}.WhenHeld(
      frc2::StartEndCommand([&] { _subClimber.ManualDrive(0.2); }, [&] { _subClimber.ManualDrive(0); }));

  frc2::JoystickButton{&_joystick0, Btn::kA}.WhenHeld(
      frc2::StartEndCommand([&] { _subClimber.ManualDrive(-0.2); }, [&] { _subClimber.ManualDrive(0); }));

  frc::SmartDashboard::PutData("Reset Climber", &_cmdResetClimb);

  frc2::POVButton LowGoalMode{&_joystick0, 180, 0};
  LowGoalMode.WhenPressed(frc2::InstantCommand{[this]{_subShooter.SetLowMode(true);}});

  frc2::POVButton HighGoalMode{&_joystick0, 0,0};
  HighGoalMode.WhenPressed(frc2::InstantCommand{[this]{_subShooter.SetLowMode(false);}});

  frc2::JoystickButton ShooterStop{&_joystick0, frc::XboxController::Button::kStart};
  ShooterStop.WhenPressed(_cmdStopShooter);

  frc2::JoystickButton ClimbUnlock{&_joystick0, Btn::kBack };
  ClimbUnlock.WhenPressed(frc2::InstantCommand([&] {_cmdClimbSequence.Schedule();} ));

  frc2::JoystickButton ClimbPistons{&_joystick0,Btn::kB};
  ClimbPistons.ToggleWhenPressed(_cmdRotateElevators);
  
  
  
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  frc2::Command* selected = _autoChooser.GetSelected();
  return selected;
}
