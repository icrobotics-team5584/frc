/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <frc/commands/Scheduler.h>
#include <frc/smartdashboard/SmartDashboard.h>

std::shared_ptr<SubDriveBase> Robot::subDriveBase;
std::shared_ptr<nt::NetworkTable> Robot::ntTable;
OI Robot::m_oi;

void Robot::RobotInit() {
  subDriveBase.reset(new SubDriveBase());

  //Setup network table
  nt::NetworkTableInstance ntTableInstance = nt::NetworkTableInstance::GetDefault();
  ntTable = ntTableInstance.GetTable("JETSON");
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
  frc::SmartDashboard::PutNumber("Joy x", m_oi.getJoystickX());
  frc::SmartDashboard::PutNumber("Joy y", m_oi.getJoystickY());

  //Put to SmartDashboard JETSON table values 
  frc::SmartDashboard::PutNumber("TARGET_X", ntTable->GetNumber("pegx", 0));
  frc::SmartDashboard::PutNumber("TARGET_Y", ntTable->GetNumber("pegy", 0));
  frc::SmartDashboard::PutNumber("VISION_FPS", ntTable->GetNumber("fps", 0));
  frc::SmartDashboard::PutNumber("VISION_STATUS", ntTable->GetNumber("status", 0));
  frc::SmartDashboard::PutNumber("VISION_HITRATE", ntTable->GetNumber("hitrate", 0));

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

void Robot::TeleopPeriodic() { frc::Scheduler::GetInstance()->Run(); }

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
