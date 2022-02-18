// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/Command.h>
#include "Utilities/JoystickScaler.h"
#include "subsystems/SubDriveBase.h"
#include "subsystems/SubShooter.h"
#include "subsystems/SubStorage.h"
#include "commands/CmdShooter.h"


#include "commands/CmdJoystickDrive.h"
#include "commands/Cmd2BallAuto.h"
#include "commands/Cmd5BallAuto.h"
#include "commands/Cmd1BallAuto.h"

#include "subsystems/SubIntake.h"
#include "commands/CmdIntake.h"
#include "commands/CmdOuttake.h"
#include "commands/CmdDeployIntake.h"
#include "commands/CmdRetractIntake.h"
#include "frc/smartdashboard/SendableChooser.h"
#include "commands/CmdTrackTarget.h"
#include "commands/CmdSpinUpShooter.h"
#include "commands/CmdStorageIn.h"
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
  SubShooter _subShooter;
  SubIntake _subIntake;
  SubStorage _subStorage;
  Autonomous _autonomous{[this]{return _subDriveBase.getYaw();}, [this]{return _subDriveBase.getDistanceTravelled();}};

  Cmd2BallAuto _cmd2BallAuto{&_subDriveBase, &_subIntake, &_subShooter, &_subStorage, &_autonomous};
  Cmd5BallAuto _cmd5BallAuto{&_subDriveBase, &_subIntake, &_subShooter, &_subStorage, &_autonomous};
  Cmd1BallAuto _cmd1BallAuto{&_subDriveBase, &_subIntake, &_subShooter, &_subStorage, &_autonomous};

 private:
  // Create new joystick to control the robot
  JoystickScaler _joystick0{0, 2.0, 2.0};

  void ConfigureButtonBindings();

  CmdShooter _cmdShooter {&_subShooter};
  CmdIntake _cmdIntake {&_subIntake};
  CmdOuttake _cmdOuttake {&_subIntake};
  CmdDeployIntake _cmdDeployIntake {&_subIntake};
  CmdRetractIntake _cmdRetractIntake {&_subIntake};
  CmdTrackTarget _cmdTrackTarget {&_subDriveBase, &_subShooter};
  CmdSpinUpShooter _cmdSpinUpShooter {&_subShooter,500};
  CmdStorageIn _cmdStorageIn {&_subStorage};
  frc::SendableChooser<frc2::Command*> _autoChooser;
  
};
