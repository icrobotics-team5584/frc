// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/Joystick.h>
#include "Utilities/JoystickScaler.h"
#include <frc2/command/Command.h>
#include <frc2/command/button/Button.h>
#include <frc2/command/button/JoystickButton.h>
#include <frc2/command/ParallelCommandGroup.h>

#include "Constants.h"

#include "subsystems/SubClimber.h"
#include "subsystems/SubColorWheel.h"
#include "subsystems/subDriveBase.h"
#include "subsystems/SubIntake.h"
#include "subsystems/SubStorage.h"
#include "subsystems/SubTurret.h"

#include "commands/CmdJoystickDrive.h"
#include "commands/CmdTrackTarget.h"
#include "commands/CmdDriveStorage.h"
#include "commands/CmdSpinColorWheel.h"
#include "commands/CmdMoveCenterColor.h"
#include "commands/CmdSpinToColor.h"
#include "commands/CmdSpinFlywheel.h"
#include "commands/CmdDeployClimber.h"
#include "commands/CmdDriveStorage.h"
#include "commands/CmdIndexStorage.h"
#include "commands/CmdIntake.h"
#include "commands/CmdJoystickDrive.h"
#include "commands/CmdSpinFlywheel.h"
#include "commands/CmdTrackTarget.h"
#include "commands/CmdClimbToPos.h"
#include "commands/CmdAuto10Ball.h"
#include "commands/CmdMoveFeeder.h"
#include "commands/CmdShoot.h"
#include "commands/CmdHomeHood.h"
#include "commands/CmdMoveStorage.h"
#include "commands/CmdDeployIntake.h"
#include "commands/CmdHomeHood.h"
#include "commands/CmdHomeTurret.h"
#include "commands/CmdClimbManual.h"
#include "commands/CmdManualClimbL.h"
#include "commands/CmdManualClimbR.h"
#include "commands/CmdDeployBrakes.h"

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
  SubTurret _subTurret;
  SubClimber _subClimber;
  //Autonomous _autonomous{ [this]{return _subDriveBase.getYaw();}, [this]{return _subDriveBase.getDistanceTravelled();}};
  CmdAuto10Ball _cmdAuto10Ball{&_subDriveBase, &_subIntake, &_subStorage, &_subTurret};
 private:
  // The robot's subsystems and commands are defined here...
  //frc::Joystick _joystick0{0};
  JoystickScaler _joystick0{0, 4.0, 4.0};

  
  SubStorage _subStorage;
  SubColorWheel _subColorWheel;
  SubIntake _subIntake; 

  CmdTrackTarget _cmdTrackTarget{&_subTurret, &_subStorage};
  CmdDriveStorage _cmdDriveStorage{&_subStorage, SubStorage::Direction::Forward, 0.2};
  CmdSpinFlywheel _cmdSpinFlywheel{&_subTurret};
  CmdDeployClimber _cmdDeployClimber{&_subClimber};
  CmdIntake _cmdIntake{&_subStorage, &_subIntake};
  CmdClimbToPos _cmdClimbToPos{&_subClimber, 20};
  CmdMoveFeeder _cmdMoveFeeder{&_subStorage};
  CmdSpinColorWheel _cmdSpinColorWheel{&_subColorWheel};
  CmdMoveCenterColor _cmdMoveCenterColor{&_subColorWheel};
  CmdSpinToColor _cmdSpinToColor{&_subColorWheel};
  CmdShoot _cmdShoot{&_subStorage, &_subTurret};
  CmdHomeHood _cmdHomeHood{&_subTurret};
  CmdHomeTurret _cmdHomeTurret{&_subTurret};
  CmdMoveStorage _cmdMoveStorage{&_subStorage, 5500};
  CmdDeployIntake _cmdDeployIntake{&_subIntake};
  CmdClimbManual _cmdClimbManual{&_subClimber};
  CmdManualClimbL _cmdManualClimbL{&_subClimber};
  CmdManualClimbR _cmdManualClimbR{&_subClimber};
  CmdDeployBrakes _cmdDeployBrakes{&_subClimber};

  void ConfigureButtonBindings();
};
