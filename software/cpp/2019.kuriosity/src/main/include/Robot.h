/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/TimedRobot.h>
#include <frc/commands/Command.h>
#include <frc/smartdashboard/SendableChooser.h>

#include "OI.h"
#include "commands/ExampleCommand.h"
#include "commands/MyAutoCommand.h"
#include "RobotMap.h"
#include "subsystems/ExampleSubsystem.h"
#include "subsystems/SubDriveBase.h"
#include "subsystems/SubElevator.h"
#include "subsystems/SubTurret.h"
#include "subsystems/SubPanelAffector.h"

#include <iostream>

using namespace std;

class Robot : public frc::TimedRobot {
 public:
  static ExampleSubsystem m_subsystem;
  static unique_ptr<OI> _oi;
  static unique_ptr<RobotMap> _robotMap;
  static unique_ptr<SubDriveBase> subDriveBase;
  static unique_ptr<SubElevator> subElevator;
  static unique_ptr<SubTurret> subTurret;
  static unique_ptr<SubPanelAffector> subPanelAffector;

  void RobotInit() override;
  void RobotPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;

 private:
  // Have it null by default so that if testing teleop it
  // doesn't have undefined behavior and potentially crash.
  //frc::Command* m_autonomousCommand = nullptr;
  //ExampleCommand m_defaultAuto;
  //MyAutoCommand m_myAuto;
  //frc::SendableChooser<frc::Command*> m_chooser;
};
