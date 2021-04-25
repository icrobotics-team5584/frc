// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdAutoTrack.h"

CmdAutoTrack::CmdAutoTrack(SubTurret* subTurret, Autonomous* autonomous) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subTurret = subTurret;
  _autonomous = autonomous;
}

// Called when the command is initially scheduled.
void CmdAutoTrack::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void CmdAutoTrack::Execute() {
  angle = _subTurret->GetTurretAngle();
  power = _autonomous->getTurretPower(_subTurret->GetTurretAngle());
  
}

// Called once the command ends or is interrupted.
void CmdAutoTrack::End(bool interrupted) {}

// Returns true when the command should end.
bool CmdAutoTrack::IsFinished() {
  return false;
}
