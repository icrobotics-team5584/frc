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
  POVButton btnDeployBreaks(&_joystick0, POVButton::Position::up);
  frc2::JoystickButton btnDeployIntake{&_joystick0, buttons::yBtn};
  frc2::JoystickButton btnSpinIntake{&_joystick0, buttons::leftBtn};
  frc2::JoystickButton btnDeployClimber{&_joystick0, buttons::xBtn};
  // frc2::JoystickButton btnManualClimb{&_joystick0, buttons::backBtn};
  frc2::JoystickButton btnManualClimbL{&_joystick0, buttons::startBtn};
  frc2::JoystickButton btnManualClimbR{&_joystick0, buttons::backBtn};
  // frc::SmartDashboard::PutData("Deploy Brakes", &_cmdDeployBrakes);

  POVButton btnHomeTurret(&_joystick0, POVButton::Position::down);

  btnDeployIntake.ToggleWhenPressed(_cmdDeployIntake);
  // btnSpinIntake.WhileHeld(_cmdIntake);
  btnSpinIntake.WhileHeld(frc2::ParallelCommandGroup{_cmdIntake, _cmdMoveStorage});
  btnTrackTarget.WhileHeld(frc2::ParallelCommandGroup{_cmdTrackTarget, _cmdShoot, _cmdMoveStorage, _cmdOnlyDeployIntake});
  btnShoot.WhileHeld(_cmdMoveFeeder);
  btnHomeTurret.WhileHeld(frc2::ParallelCommandGroup{_cmdHomeHood, _cmdHomeTurret});
  btnManualClimbL.WhileHeld(_cmdManualClimbL);
  btnManualClimbR.WhileHeld(_cmdManualClimbR);
  btnDeployClimber.WhileHeld(_cmdDeployClimber);
  btnDeployBreaks.ToggleWhenPressed(_cmdDeployBrakes);

  //TODO: Intake Toggle Up/Down (Right Trigger)
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return &_cmdAuto10Ball;
}
