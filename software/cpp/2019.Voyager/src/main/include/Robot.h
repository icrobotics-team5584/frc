/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Commands/Command.h>
#include <SmartDashboard/SendableChooser.h>
#include <TimedRobot.h>
#include "RobotMap.h"
#include "Commands/ExampleCommand.h"
#include "Commands/MyAutoCommand.h"
#include "OI.h"
#include "Subsystems/ExampleSubsystem.h"
#include "Subsystems/SubDriveBase.h"
#include "Commands/UlsTest.h"

using namespace std;

class Robot : public frc::TimedRobot {
 public:
  static ExampleSubsystem m_subsystem;
  static unique_ptr<OI> _oi;
  static unique_ptr<RobotMap> _robotMap;
  static unique_ptr<SubDriveBase> subDriveBase;

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
  // frc::Command* m_autonomousCommand = nullptr;
  // ExampleCommand m_defaultAuto;
  // MyAutoCommand m_myAuto;
  // frc::SendableChooser<frc::Command*> m_chooser;
  Timer timer;
  unique_ptr<UlsTest> _ulsTest;
};
