/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <frc/commands/Scheduler.h>
#include <frc/smartdashboard/SmartDashboard.h>

std::unique_ptr<SubDriveBase> Robot::subDriveBase;
std::unique_ptr<SubShooter> Robot::subShooter;
std::unique_ptr<SubStorage> Robot::subStorage;
OI Robot::m_oi;


void Robot::RobotInit() {
  subDriveBase.reset(new SubDriveBase());
  subShooter.reset(new SubShooter());
  subStorage.reset(new SubStorage());

}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {

  frc::SmartDashboard::PutNumber("Right RPM",subShooter->GetRightRPM());
  frc::SmartDashboard::PutNumber("Left RPM", subShooter->GetLeftRPM());
  subShooter->speed = frc::SmartDashboard::GetNumber("Motor Speed", subShooter->speed);
  frc::SmartDashboard::PutNumber("Motor Speed", subShooter->speed);

  RPM = frc::SmartDashboard::GetNumber("RPM", RPM);
  frc::SmartDashboard::PutNumber("RPM", RPM);


  frc::SmartDashboard::PutNumber("Joy x", m_oi.getJoystickX());
  frc::SmartDashboard::PutNumber("Joy y", m_oi.getJoystickY());
  
}

/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() { frc::Scheduler::GetInstance()->Run(); }

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString code to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional commands to the
 * chooser code above (like the commented example) or additional comparisons to
 * the if-else structure below with additional strings & commands.
 */
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

    double targetVelocity_UnitsPer100ms = RPM * 4096 / 600  ;
    subShooter->leftMotor->Set(ControlMode::Velocity, targetVelocity_UnitsPer100ms); 
    subShooter->rightMotor->Set(ControlMode::Velocity, -targetVelocity_UnitsPer100ms+80);
  
  
  frc::Scheduler::GetInstance()->Run(); 
  }

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
