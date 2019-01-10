/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/UlsTest.h"
#include "Robot.h"
#include <iostream>

UlsTest::UlsTest() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::subDriveBase.get());
}

// Called just before this Command runs the first time
void UlsTest::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void UlsTest::Execute() {
  std::cout << "Execute: " << true << std::endl;
  double angle = Robot::subDriveBase->getYaw();
  Robot::subDriveBase->drive(0.7, -0.2);
}

// Make this return true when this Command no longer needs to run execute()
bool UlsTest::IsFinished() { 
  frc::SmartDashboard::PutBoolean("Has ended", Robot::subDriveBase->hasReachedLine());
  return Robot::subDriveBase->hasReachedLine();
}
// Called once after isFinished returns true
void UlsTest::End() {
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void UlsTest::Interrupted() {}
