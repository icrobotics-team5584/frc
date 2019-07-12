/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdInspireArm.h"

CmdInspireArm::CmdInspireArm(Angle angle) {
  //Okay, now you can call CmdInspireArm with an "ArmState(FLOOR)" in the function (for example)
  
  // POSSIBLE ARM POSITIONS //
  //         FLOOR          //
  //         HATCH          //
  //          SKY           //
  //          HAB           //

  int _angle = angle

  Requires(Robot::subEncodedArm.get());
}

// Called just before this Command runs the first time
void CmdInspireArm::Initialize() {
  Robot::subEncodedArm->ConfigTalon();
}

// Called repeatedly when this Command is scheduled to run
void CmdInspireArm::Execute() {
  //grab values from shuffleboard. Once the system is tuned this should be deleted.
  kP = SmartDashboard::GetNumber("kP", 0.1);
  kI = SmartDashboard::GetNumber("kI", 0);
  kD = SmartDashboard::GetNumber("kD", 0);

  cruiseVelocity = SmartDashboard::GetNumber("cruiseVelocity", 300);
  maxAcceleration = SmartDashboard::GetNumber("maxAcceleration", 300);
  
  angle = _angle //Get inputs from the code (with the four preset positions from the enumerator.)
  //angle = SmartDashboard::GetNumber("setAngle", 0); //Get inputs from shuffleboard. This is disabled cause we're not manually setting anything anymore.

  //set feedfoward
  position = Robot::subEncodedArm->getEncoder();
  angleRadians = Robot::subEncodedArm->getAngle() * (3.14/180);
  kF = 0.2 * 1023;

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
