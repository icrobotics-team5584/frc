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
#include "subsystems/SubIntake.h"
#include "commands/CmdIntake.h"
#include "commands/CmdOuttake.h"
#include "commands/CmdDeployIntake.h"
#include "commands/CmdRetractIntake.h"
#include "commands/CmdTrackTarget.h"
#include "commands/CmdSpinUpShooter.h"
#include "commands/CmdStorageIn.h"
#include "subsystems/SubClimber.h"
#include "commands/CmdExtendClimber.h"
#include "commands/CmdRetractClimber.h"
#include <frc2/command/InstantCommand.h>


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

  SubShooter _subShooter;
  SubIntake _subIntake;
  SubStorage _subStorage;
  SubClimber _subClimber;

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
  CmdExtendClimber _cmdExtendClimber {&_subClimber};
  CmdRetractClimber _cmdRetractClimber {&_subClimber};

  frc2::InstantCommand _cmdLockClimber{[&]{_subClimber.Lock();}};
  frc2::InstantCommand _cmdUnlockClimber{[&]{_subClimber.Unlock();}};
  frc2::InstantCommand _cmdRotateClimber{[&]{_subClimber.Rotate();}};
  frc2::InstantCommand _cmdStowClimber{[&]{_subClimber.Stow();}};
  frc2::InstantCommand _cmdNearExtend{[&]{_subClimber.DriveTo(90);}};
  frc2::InstantCommand _cmdResetClimbSeq{[&]{_subClimber.ResetClimbSequence();}};
};
