// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdAutoCircle.h"

CmdAutoCircle::CmdAutoCircle(SubDriveBase* subDriveBase) : _autonomous{
  [subDriveBase]{return subDriveBase->getYaw();}, 
  [subDriveBase]{return subDriveBase->getDistanceTravelled();}
}{
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(subDriveBase);
  _subDriveBase = subDriveBase;
}

// Called when the command is initially scheduled.
void CmdAutoCircle::Initialize() {
  _subDriveBase->resetYaw();
  _autonomous.setPosition(0,0);

}

// Called repeatedly when this Command is scheduled to run
void CmdAutoCircle::Execute() {
  driveInput = _autonomous.autoDrive(100.05, 0, 100);
  _subDriveBase->drive(driveInput.speed, driveInput.steering);
}

// Called once the command ends or is interrupted.
void CmdAutoCircle::End(bool interrupted) {}

// Returns true when the command should end.
bool CmdAutoCircle::IsFinished() {
  return false;
}
