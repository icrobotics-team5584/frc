// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/Command.h>
#include <frc/Joystick.h>
#include <sendableSparkMax.h>

#include "Constants.h"

//Subsystems
#include "subsystems/subDriveBase.h"
#include "subsystems/SubTurret.h"

//Commands
#include "commands/cmdDrive.h"
#include "commands/CmdTrackTarget.h"
#include "commands/CmdHomeTurret.h"

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
  CmdHomeTurret cmdHomeTurret;

 private:
  // The robot's subsystems and commands are defined here...
  subDriveBase SubDriveBase;
  SubTurret subTurret;

  cmdDrive CmdDrive;
  CmdTrackTarget cmdTrackTarget;

  sendableSparkMax SPMTest1;
  sendableSparkMax SPMTest2;
  sendableSparkMax SPMTest3;

  frc::Joystick driverController{ContainerConstants::kDriverControllerPort};

  void ConfigureButtonBindings();
};
