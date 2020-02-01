/*----------------------------------------------------------------------------*/
/* Robot.h                                                                    */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/TimedRobot.h>
#include <frc/commands/Command.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/Timer.h>

#include "OI.h"
#include "subsystems/SubShooter.h"
#include "subsystems/SubDriveBase.h"
#include "subsystems/SubStorage.h"
#include "subsystems/SubIntake.h"
#include "commands/CmdResetGyro.h"
#include "subsystems/SubClimber.h"
#include "subsystems/SubBuddyClimb.h"

#include "Utilities/PosEncoderGyro.h"


class Robot : public frc::TimedRobot {
 public:
  static OI m_oi;
  static std::shared_ptr<SubShooter> subShooter;
  static std::shared_ptr<SubBuddyClimb> subBuddyClimb;
  static std::shared_ptr<SubClimber> subClimber;
  static std::shared_ptr<SubStorage> subStorage;
  static std::shared_ptr<SubIntake> subIntake;
  static std::shared_ptr<SubDriveBase> subDriveBase;
  static std::shared_ptr<PosEncoderGyro> posEncoderGyro;
  static std::shared_ptr<CmdResetGyro> cmdResetGyro;
  static std::shared_ptr<frc::Timer> timer;
  
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
