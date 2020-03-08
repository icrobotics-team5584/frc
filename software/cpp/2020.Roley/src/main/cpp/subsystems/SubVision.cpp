/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SubVision.h"
#include "Robot.h"

#include <frc/smartdashboard/SmartDashboard.h>


SubVision::SubVision() : Subsystem("ExampleSubsystem") {}

void SubVision::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

void SubVision::Periodic() {
  frc::SmartDashboard::PutNumber("TARGET_X", Robot::ntTable->GetNumber("pegx", 0));
  frc::SmartDashboard::PutNumber("TARGET_Y", Robot::ntTable->GetNumber("pegy", 0));
  frc::SmartDashboard::PutNumber("TARGET_DIST", Robot::ntTable->GetNumber("pegrange", 0));
  frc::SmartDashboard::PutNumber("VISION_FPS", Robot::ntTable->GetNumber("fps", 0));
  frc::SmartDashboard::PutNumber("VISION_STATUS", Robot::ntTable->GetNumber("status", 0));
  frc::SmartDashboard::PutNumber("VISION_HITRATE", Robot::ntTable->GetNumber("hitrate", 0));

  pegPos = Robot::ntTable->GetNumber("pegy", 0);
  pegHeight = Robot::ntTable->GetNumber("pegx", 0);


  frc::SmartDashboard::PutNumber("Target Position in FOV", pegPos);

  if (Robot::ntTable->GetNumber("hitrate", 1) == 0 && pegPos > -15 && pegPos < 15 && pegHeight < -15)
  {
    frc::SmartDashboard::PutBoolean("Target in Shooting Range", true);
  }
  else
  {
    frc::SmartDashboard::PutBoolean("Target in Shooting Range", false);
  }
}

double GetX() {
  return Robot::ntTable->GetNumber("pegx", 0);
}

double GetY() {
  return Robot::ntTable->GetNumber("pegy", 0);
}

double GetDist() {
  return Robot::ntTable->GetNumber("pegrange", 0);
}

double GetFPS() {
  return Robot::ntTable->GetNumber("fps", 0);
}

double GetHitrate() {
  return Robot::ntTable->GetNumber("hitrate", 0);
}

bool CanSeeTarget() {
  if (Robot::ntTable->GetNumber("hitrate", 1) == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}