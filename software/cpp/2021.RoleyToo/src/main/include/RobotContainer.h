// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/Joystick.h>
#include <frc2/command/Command.h>

#include "subsystems/subDriveBase.h"
#include "Utilities/Autonomous.h"
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
  SubDriveBase _subDriveBase;
  Autonomous _autonomous{ [this]{return _subDriveBase.getYaw();}, [this]{return _subDriveBase.getDistanceTravelled();}
  };
 private:
  // The robot's subsystems and commands are defined here...
  frc::Joystick _joystick0{0};

  void ConfigureButtonBindings();
};
