// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/controller/PIDController.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc2/command/Command.h>
#include <frc2/command/InstantCommand.h>
#include <frc2/command/PIDCommand.h>
#include <frc2/command/ParallelRaceGroup.h>
#include <frc2/command/RunCommand.h>
#include <wpi/fs.h>
#include <frc/Filesystem.h>
#include <frc/trajectory/Trajectory.h>
#include <frc/trajectory/TrajectoryGenerator.h>
#include <frc/trajectory/TrajectoryUtil.h>


#include "Utilities/JoystickScaler.h"
#include "subsystems/SubDriveBase.h"
#include "commands/CmdJoystickDrive.h"

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

    fs::path deployDirectory = frc::filesystem::GetDeployDirectory() + "/Paths/MoveForward.wpilib.json";
    frc::Trajectory trajectory{frc::TrajectoryUtil::FromPathweaverJson(deployDirectory.string())};

 private:
  // Create new joystick to control the robot
  JoystickScaler _joystick0{0, 2.0, 2.0};

  // The chooser for the autonomous routines
  frc::SendableChooser<frc2::Command*> _chooser;

  void ConfigureButtonBindings();
};
