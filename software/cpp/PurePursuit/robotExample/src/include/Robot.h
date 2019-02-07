#pragma once

#include <Commands/Command.h>
#include <SmartDashboard/SendableChooser.h>
#include <TimedRobot.h>
#include "OI.h"
#include "RobotMap.h"
#include "Subsystems/SubDriveBase.h"
#include "Commands/CmdMakePath.h"


using namespace std;

class Robot : public frc::TimedRobot {
 public:
  static shared_ptr<SubDriveBase> subDriveBase;
  static shared_ptr<OI> oi;
  static shared_ptr<RobotMap> robotMap;
  unique_ptr<CmdMakePath> cmdMakePath;

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
};
