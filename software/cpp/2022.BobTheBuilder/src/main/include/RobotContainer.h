// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/Command.h>
#include "Utilities/JoystickScaler.h"
#include "subsystems/SubDriveBase.h"
#include "subsystems/SubShooter.h"
#include "commands/CmdShooter.h"


#include "commands/CmdJoystickDrive.h"
#include "commands/Cmd2BallAuto.h"
#include "commands/Cmd5BallAuto.h"

#include "subsystems/SubIntake.h"
#include "commands/CmdIntake.h"
#include "commands/CmdOuttake.h"
#include "commands/CmdDeployIntake.h"
#include "commands/CmdRetractIntake.h"
#include "frc/smartdashboard/SendableChooser.h"

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
  Cmd2BallAuto _cmd2BallAuto{&_subDriveBase};
  Cmd5BallAuto _cmd5BallAuto;

  SubShooter _subShooter;
  SubIntake _subIntake;

 private:
  // Create new joystick to control the robot
  JoystickScaler _joystick0{0, 2.0, 2.0};

  void ConfigureButtonBindings();

  CmdShooter _cmdShooter {&_subShooter};
  CmdIntake _cmdIntake {&_subIntake};
  CmdOuttake _cmdOuttake {&_subIntake};
  CmdDeployIntake _cmdDeployIntake {&_subIntake};
  CmdRetractIntake _cmdRetractIntake {&_subIntake};

  frc::SendableChooser<frc2::Command*> _autoChooser;

};
