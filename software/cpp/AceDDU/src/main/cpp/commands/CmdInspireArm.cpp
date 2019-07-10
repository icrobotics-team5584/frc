/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdInspireArm.h"

CmdInspireArm::CmdInspireArm() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::subEncodedArm.get());
}

// Called just before this Command runs the first time
void CmdInspireArm::Initialize() {
  Robot::subEncodedArm->ConfigTalon();
}

// Called repeatedly when this Command is scheduled to run
void CmdInspireArm::Execute() {
  //grab values from shuffleboard
  kP = SmartDashboard::GetNumber("kP", 0.1);
  kI = SmartDashboard::GetNumber("kI", 0.1);
  kD = SmartDashboard::GetNumber("kD", 0.1);

  cruiseVelocity = SmartDashboard::GetNumber("cruiseVelocity", 300);
  maxAcceleration = SmartDashboard::GetNumber("maxAcceleration", 300);

  angle = SmartDashboard::GetNumber("setAngle", 0);

  //set feedfoward
  position = Robot::subEncodedArm->getEncoder();
  angleRadians = Robot::subEncodedArm->getAngle() * (3.14/180);
  kF = 0.2;

  Robot::subEncodedArm->srxArmFront->Config_kF(0, kF, 0);

  //delete this once tuned
   Robot::subEncodedArm->srxArmFront->Config_kP(0, kP, 0);
   Robot::subEncodedArm->srxArmFront->Config_kI(0, kI, 0);
   Robot::subEncodedArm->srxArmFront->Config_kD(0, kD, 0);
   Robot::subEncodedArm->srxArmFront->ConfigMotionCruiseVelocity(cruiseVelocity, 0);
   Robot::subEncodedArm->srxArmFront->ConfigMotionAcceleration(maxAcceleration, 0);

  Robot::subEncodedArm->SetPosition(angle);
}

// Make this return true when this Command no longer needs to run execute()
bool CmdInspireArm::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdInspireArm::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdInspireArm::Interrupted() {}
