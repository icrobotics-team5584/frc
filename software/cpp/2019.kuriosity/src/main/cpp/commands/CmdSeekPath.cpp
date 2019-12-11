/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdSeekPath.h"
#include "Robot.h"
#include "pathfinder.h"

CmdSeekPath::CmdSeekPath() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::subDriveBase.get());
  posEncoderGyro.reset(new PosEncoderGyro);
  dvoTank.reset(new DvoTank);
  Segment * seg = Robot::subDriveBase->generatePath();
  int pathLength = Robot::subDriveBase->getPathLength();
  pathFollower.reset(new PathFollower(seg, pathLength, posEncoderGyro, dvoTank));
}

// Called just before this Command runs the first time
void CmdSeekPath::Initialize() {
  pathFollower->reset();
  Robot::subDriveBase->zeroEncoders();
  Robot::subDriveBase->setTalControlMode(ControlMode::PercentOutput);
  scaleFactor = wheelCircumference/4096;
  std::cout << "yes" << std::endl;  
}

// Called repeatedly when this Command is scheduled to run
void CmdSeekPath::Execute() {
  //pathFollower->followPath();
  kF = 1023/ (3.6/ 0.000078 / 10);
  kP = SmartDashboard::GetNumber("Vel P", 0);
  kI = SmartDashboard::GetNumber("Vel I", 0);
  kD = SmartDashboard::GetNumber("Vel D", 0);
  targetVelocity = SmartDashboard::GetNumber("Target Vel", 0);
  Robot::subDriveBase->velocityPIDConfig(kF, kP, kI, kD);
  double leftVelocity = (targetVelocity / scaleFactor / 10);
  double rightVelocity = -1.0*(targetVelocity / scaleFactor / 10);
  SmartDashboard::PutNumber("PID velocityL", Robot::subDriveBase->getLeftVelocity());
  SmartDashboard::PutNumber("PID velocityR", Robot::subDriveBase->getRightVelocity());
  Robot::subDriveBase->tankDriveVelocity(leftVelocity, rightVelocity);
}

// Make this return true when this Command no longer needs to run execute()
bool CmdSeekPath::IsFinished() { 
  return false;
}

// Called once after isFinished returns true
void CmdSeekPath::End() {
  //SmartDashboard::PutBoolean("Running CmdSeekpath", false);
  Robot::subDriveBase->drive(0.0, 0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdSeekPath::Interrupted() {
  End();
}
