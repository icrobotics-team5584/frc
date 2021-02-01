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

RobotContainer::RobotContainer() {
  // Initialize all of your commands and subsystems here
  _subDriveBase.SetDefaultCommand(CmdJoystickDrive(&_subDriveBase, &_joystick0));
  _subStorage.SetDefaultCommand(CmdIndexStorage(&_subStorage));
  // Configure the button bindings
  ConfigureButtonBindings();

}

void RobotContainer::ConfigureButtonBindings() {
  // Configure your button bindings here
  frc2::JoystickButton btnIntake{&_joystick0, buttons::leftBtn};
  frc2::JoystickButton btnClimbToPos{&_joystick0, buttons::rightBtn};
  AxisButton btnTrackTarget{&_joystick0, buttons::leftTrigger};
  AxisButton btnShoot{&_joystick0, buttons::rightTrigger};
  POVButton btnDeployClimber{&_joystick0, POVButton::Position::up};
  frc2::JoystickButton xBtn{&_joystick0, buttons::xBtn};
  
  btnTrackTarget.WhileHeld(_cmdTrackTarget);
  btnShoot.WhileHeld(_cmdSpinFlywheel);
  btnDeployClimber.WhenPressed(_cmdDeployClimber);
  btnIntake.WhenPressed(_cmdIntake);
  btnClimbToPos.WhileHeld(_cmdClimbToPos);
  xBtn.WhenHeld(frc2::SequentialCommandGroup{_cmdSpinColorWheel, _cmdMoveCenterColor, _cmdSpinToColor}); 
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return &_cmdAutoCircle;
}
