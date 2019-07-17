/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <iostream>

#include "Robot.h"
#include "commands/Auto_rocket.h"
#include <frc/commands/Scheduler.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include "subsystems/SubEncodedArm.h"


std::unique_ptr<OI> Robot::m_oi;
std::unique_ptr<SubDrivebase> Robot::subDrivebase;
std::unique_ptr<SubEncodedArm> Robot::subEncodedArm;
std::unique_ptr<SubClimber> Robot::subClimber;

void Robot::RobotInit() {
  std::cout << "RobotInit" << std::endl;
  subDrivebase.reset(new SubDrivebase);
  subEncodedArm.reset(new SubEncodedArm);
  subClimber.reset(new SubClimber);
  cs::UsbCamera camera = CameraServer::GetInstance()->StartAutomaticCapture();
  std::cout << "SubFinished" << std::endl;
  m_oi.reset(new OI);
  std::cout << "m_oi Finished" << std::endl;
  autoRocket.reset(new Auto_rocket);

  std::cout << "Init Finished" << std::endl;

  //Zero out/Initialize values on Shuffleboard
  

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
  //std::cout << "PeriodicStart" << std::endl;
  //frc::SmartDashboard::PutNumber("Angle", subDrivebase->get_angle());
  //frc::SmartDashboard::PutNumber("Distance", subDrivebase->get_distance());
  frc::SmartDashboard::PutNumber("Arm Angle", subEncodedArm->getAngle());
  //std::cout << "PeriodicEnd" << std::endl;
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

  //autoRocket->Start();
  
  // std::string autoSelected = frc::SmartDashboard::GetString(
  //     "Auto Selector", "Default");
  // if (autoSelected == "My Auto") {
  //   m_autonomousCommand = &m_myAuto;
  // } else {
  //   m_autonomousCommand = &m_defaultAuto;
  // }

}

void Robot::AutonomousPeriodic() 
{ 
  frc::Scheduler::GetInstance()->Run();
  
}

void Robot::TeleopInit() {
  // This makes sure that the autonomous stops running when
  // teleop starts running. If you want the autonomous to
  // continue until interrupted by another command, remove
  // this line or comment it out.
  SmartDashboard::PutNumber("kF", 0);
  SmartDashboard::PutNumber("kP", 0);
  SmartDashboard::PutNumber("kI", 0);
  SmartDashboard::PutNumber("kD", 0);

  SmartDashboard::PutNumber("cruiseVelocity", 300);
  SmartDashboard::PutNumber("maxAcceleration", 300);

  SmartDashboard::PutNumber("setAngle", 0);

  frc::SmartDashboard::PutNumber("Arm Speed", 0);
}



void Robot::TeleopPeriodic() { frc::Scheduler::GetInstance()->Run(); }

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
