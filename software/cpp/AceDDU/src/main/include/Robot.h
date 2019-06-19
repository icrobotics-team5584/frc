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
class Auto_rocket;
//class CmdMoveArm;

#include "commands/CmdMoveArm.h"


#include<subsystems/SubDrivebase.h>
#include<subsystems/SubIntake.h>
#include "OI.h"
#include "subsystems/SubEncodedArm.h"


class Robot : public frc::TimedRobot {
 public:
  static std::unique_ptr <OI> m_oi;

  void RobotInit() override;
  void RobotPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;
  static std::unique_ptr<SubDrivebase> subDrivebase;
  static std::unique_ptr<SubEncodedArm> subEncodedArm;
  static std::unique_ptr<SubIntake> subIntake;

 private:
  std::unique_ptr<Auto_rocket> autoRocket;
  // Have it null by default so that if testing teleop it
  // doesn't have undefined behavior and potentially crash.
  frc::SendableChooser<frc::Command*> m_chooser;
  std::unique_ptr<CmdMoveArm> cmdMoveArm;
};
