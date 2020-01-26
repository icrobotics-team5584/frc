/*----------------------------------------------------------------------------*/
/*Robot.cpp                                                                   */
/*----------------------------------------------------------------------------*/

#include <frc/commands/Scheduler.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include "Robot.h"

std::unique_ptr<SubShooter> Robot::subShooter;
std::unique_ptr<SubStorage> Robot::subStorage;
std::unique_ptr<SubIntake> Robot::subIntake;
std::shared_ptr<SubDriveBase> Robot::subDriveBase;
std::shared_ptr<PosEncoderGyro> Robot::posEncoderGyro;
std::shared_ptr<CmdResetGyro> Robot::cmdResetGyro;
OI Robot::m_oi;


void Robot::RobotInit() {

  //Reset subsystems
  subDriveBase.reset(new SubDriveBase());
  subIntake.reset(new SubIntake);
  subShooter.reset(new SubShooter());
  subStorage.reset(new SubStorage());

  //Reset Auto Encoder
  posEncoderGyro.reset(new PosEncoderGyro());
  //Auto CMD Reset
  cmdResetGyro.reset(new CmdResetGyro());
  //Auto INIT process
  posEncoderGyro->reset();
  //Enable cmd yaw to be run without being cancelled
  cmdResetGyro->SetRunWhenDisabled(true);
  //Runs a cmd that waits for th navx to stop calibrating then resets gyro
  cmdResetGyro->Start();
  
  //std::cout << "robot init" << std::endl;
}


void Robot::RobotPeriodic() {

  frc::SmartDashboard::PutNumber("Right RPM",subShooter->GetRightRPM());
  frc::SmartDashboard::PutNumber("Left RPM", subShooter->GetLeftRPM());
  subShooter->speed = frc::SmartDashboard::GetNumber("Motor Speed", subShooter->speed);
  frc::SmartDashboard::PutNumber("Motor Speed", subShooter->speed);

  frc::SmartDashboard::PutNumber("Joy x", m_oi.getJoystickX());
  frc::SmartDashboard::PutNumber("Joy y", m_oi.getJoystickY());
  posEncoderGyro->updateAbsolutePosition();
  posEncoderGyro->updateRelativePosition();
}


void Robot::DisabledInit() {}


void Robot::DisabledPeriodic() { frc::Scheduler::GetInstance()->Run(); }


void Robot::AutonomousInit() {
  // std::string autoSelected = frc::SmartDashboard::GetString(
  //     "Auto Selector", "Default");
  // if (autoSelected == "My Auto") {
  //   m_autonomousCommand = &m_myAuto;
  // } else {
  //   m_autonomousCommand = &m_defaultAuto;
  // }
}

void Robot::AutonomousPeriodic() { frc::Scheduler::GetInstance()->Run(); }


void Robot::TeleopInit() {
  // This makes sure that the autonomous stops running when
  // teleop starts running. If you want the autonomous to
  // continue until interrupted by another command, remove
  // this line or comment it out.
}


void Robot::TeleopPeriodic() { 
  
  frc::Scheduler::GetInstance()->Run(); 
  }

void Robot::TestPeriodic() {}


#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
