/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/TimedRobot.h>
#include <frc/commands/Command.h>
#include <frc/smartdashboard/SendableChooser.h>

#include "OI.h"
#include "subsystems/SubShooter.h"
#include "subsystems/SubDriveBase.h"
#include "subsystems/SubStorage.h"
#include "Utilities/PosEncoderGyro.h"
#include "commands/CmdResetGyro.h"

#include "subsystems/SubIntake.h"

#include "commands/CmdAutoRoutineOne.h"
#include "commands/CmdAutoRoutineTwo.h"


class Robot : public frc::TimedRobot {
 public:
  

  static std::unique_ptr<OI> oi;
  static std::unique_ptr<SubShooter> subShooter;
  static std::unique_ptr<SubStorage> subStorage;
  static std::shared_ptr<SubDriveBase> subDriveBase;
  static std::shared_ptr<PosEncoderGyro> posEncoderGyro;
  static std::shared_ptr<CmdResetGyro> cmdResetGyro;
  
  void RobotInit() override;
  void RobotPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;

  static std::unique_ptr<SubIntake> subIntake;

 private:
  frc::Command* autonomousCommand;
  CmdAutoRoutineOne* autoOne;
  CmdAutoRoutineTwo* autoTwo;
  frc::SendableChooser<frc::Command*> chooser;
};
