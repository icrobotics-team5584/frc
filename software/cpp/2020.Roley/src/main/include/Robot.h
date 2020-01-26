/*----------------------------------------------------------------------------*/
/* Robot.h                                                                    */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/TimedRobot.h>
#include <frc/commands/Command.h>
#include <frc/smartdashboard/SendableChooser.h>

#include "OI.h"
#include "subsystems/SubShooter.h"
#include "subsystems/SubDriveBase.h"
#include "subsystems/SubStorage.h"
#include "subsystems/SubIntake.h"

#include "commands/CmdResetGyro.h"

#include "Utilities/PosEncoderGyro.h"


class Robot : public frc::TimedRobot {
 public:
  static OI m_oi;
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
  // Have it null by default so that if testing teleop it
  // doesn't have undefined behavior and potentially crash.
  //frc::Command* m_autonomousCommand = nullptr;
  //ExampleCommand m_defaultAuto;
  //MyAutoCommand m_myAuto;
  //frc::SendableChooser<frc::Command*> m_chooser;
};
