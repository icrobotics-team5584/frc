// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

#include "frc2/command/button/JoystickButton.h"
#include "Utilities/ButtonPOV.h"
#include "Utilities/AxisButton.h"

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
  frc2::JoystickButton bBtn{&_joystick0, buttons::bBtn};
  frc2::JoystickButton btnDeployIntake{&_joystick0, buttons::aBtn};
  frc2::JoystickButton btnRetractIntake{&_joystick0, buttons::bBtn};
  frc2::JoystickButton btnIntake{&_joystick0, buttons::xBtn};
  frc2::JoystickButton btnOuttake{&_joystick0, buttons::yBtn};
  ButtonPOV btnDeployClimber{&_joystick0, POVPositions::upBtn};
  AxisButton btnTrackTarget{&_joystick0, buttons::leftTrigger};
  AxisButton btnShoot{&_joystick0, buttons::rightTrigger};
  

  btnTrackTarget.WhileHeld(_cmdTrackTarget);
  aBtn.WhileHeld(_cmdDriveStorage);
  btnShoot.WhileHeld(_cmdSpinFlywheel);
  bBtn.WhileHeld(_cmdHomeTurret);
  btnDeployClimber.WhenPressed(_cmdDeployClimber);

  btnDeployIntake.WhenPressed([this]{_subIntake.Deploy();});
  btnRetractIntake.WhenPressed([this]{_subIntake.Retract();});
  btnIntake.WhenPressed([this]{_subIntake.Intake();});
  btnOuttake.WhenPressed([this]{_subIntake.Outtake();});  
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return &_cmdAutoCircle;
}
