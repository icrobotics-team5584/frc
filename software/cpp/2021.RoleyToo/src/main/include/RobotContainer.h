// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/Joystick.h>
#include "Utilities/JoystickScaler.h"
#include <frc2/command/Command.h>
#include <frc2/command/button/Button.h>
#include <frc2/command/button/JoystickButton.h>

#include "subsystems/SubColorWheel.h"
#include "subsystems/SubClimber.h"
#include "subsystems/subDriveBase.h"
#include "subsystems/SubIntake.h"
#include "Constants.h"

#include "subsystems/SubDriveBase.h"
#include "subsystems/SubTurret.h"
#include "subsystems/SubStorage.h"
#include "utilities/Autonomous.h"

#include "commands/CmdAutoCircle.h"
#include "commands/CmdJoystickDrive.h"
#include "commands/CmdTrackTarget.h"
#include "commands/CmdDriveStorage.h"
#include "commands/CmdSpinFlywheel.h"
#include "commands/CmdDeployClimber.h"
#include "commands/CmdIntake.h"
#include "commands/CmdIndexStorage.h"
#include "commands/CmdClimbToPos.h"

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
  SubDriveBase _subDriveBase;
  //Autonomous _autonomous{ [this]{return _subDriveBase.getYaw();}, [this]{return _subDriveBase.getDistanceTravelled();}};
  CmdAutoCircle _cmdAutoCircle{&_subDriveBase};
 private:
  // The robot's subsystems and commands are defined here...
  //frc::Joystick _joystick0{0};
  JoystickScaler _joystick0{0, 3.0, 3.0};

  SubTurret _subTurret;
  SubStorage _subStorage;
  SubClimber _subClimber;
  SubColorWheel _subColorWheel;
  SubIntake _subIntake; 

  CmdTrackTarget _cmdTrackTarget{&_subTurret};
  CmdDriveStorage _cmdDriveStorage{&_subStorage, SubStorage::Direction::Forward, 0.2};
  CmdSpinFlywheel _cmdSpinFlywheel{&_subTurret};
  CmdDeployClimber _cmdDeployClimber{&_subClimber};
  CmdHomeTurret _cmdHomeTurret{&_subTurret};
  CmdIntake _cmdIntake{&_subStorage, &_subIntake};
  CmdClimbToPos _cmdClimbToPos{&_subClimber, 200};

  void ConfigureButtonBindings();
};
