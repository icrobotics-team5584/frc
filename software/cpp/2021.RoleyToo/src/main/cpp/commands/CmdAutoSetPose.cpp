// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdAutoSetPose.h"
CmdAutoSetPose::CmdAutoSetPose(Autonomous* autonomous, double x, double y, double angle) {
  // Use addRequirements() here to declare subsystem dependencies.
  _autonomous = autonomous;
  _x = x;
  _y = y;
  _angle = angle;
}

// Called when the command is initially scheduled.
void CmdAutoSetPose::Initialize() 
{
  _autonomous->setPosition(_x, _y);
  _autonomous->setAngle(_angle);
}

// Called repeatedly when this Command is scheduled to run
void CmdAutoSetPose::Execute() {}

// Called once the command ends or is interrupted.
void CmdAutoSetPose::End(bool interrupted) {}

// Returns true when the command should end.
bool CmdAutoSetPose::IsFinished() {
  return true;
}
