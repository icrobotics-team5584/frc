// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/Joystick.h>
#include <frc2/command/Command.h>
#include <frc2/command/button/Button.h>
#include <frc2/command/button/JoystickButton.h>

#include "subsystems/subDriveBase.h"
#include "subsystems/SubIntake.h"
#include "Constants.h"

/**
 * This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the {@link Robot} periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and button mappings) should be declared here.
 */
class RobotContainer {
 public:
  RobotContainer();

  frc2::Command* GetAutonomousCommand();

 private:
  // The robot's subsystems and commands are defined here...
  frc::Joystick _joystick0{0};

  SubDriveBase _subDriveBase;

  SubIntake _subIntake; 

  frc2::JoystickButton btnDeployIntake{&_joystick0, buttons::aBtn};
  frc2::JoystickButton btnRetractIntake{&_joystick0, buttons::bBtn};
  frc2::JoystickButton btnIntake{&_joystick0, buttons::xBtn};
  frc2::JoystickButton btnOuttake{&_joystick0, buttons::yBtn};

  void ConfigureButtonBindings();
};
