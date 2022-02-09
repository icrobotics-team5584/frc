// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdTrackTarget.h"

CmdTrackTarget::CmdTrackTarget(SubDriveBase* subDriveBase, SubShooter* subShooter) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subDriveBase = subDriveBase;
  _subShooter = subShooter;
  AddRequirements(_subDriveBase);
  AddRequirements(_subShooter);
}

// Called when the command is initially scheduled.
void CmdTrackTarget::Initialize() {
  _subDriveBase->drive(0.0, 0.0, false);
}

// Called repeatedly when this Command is scheduled to run
void CmdTrackTarget::Execute() {
  if (_subShooter->GetLimelight().tx > 0 + VisionToleranceLevel) {
    _subDriveBase->drive(0.0, -0.12, false);
  }
  else if (_subShooter->GetLimelight().tx < 0 - VisionToleranceLevel) {
    _subDriveBase->drive(0.0, 0.12, false);
  }
  else {
    _subDriveBase->drive(0.0, 0.0, false);
  }
}

// Called once the command ends or is interrupted.
void CmdTrackTarget::End(bool interrupted) {
  _subDriveBase->drive(0.0, 0.0, false);
}

// Returns true when the command should end.
bool CmdTrackTarget::IsFinished() {
  return false;
}
