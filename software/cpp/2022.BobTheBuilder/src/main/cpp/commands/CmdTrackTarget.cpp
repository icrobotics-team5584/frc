// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdTrackTarget.h"
#include <frc/smartdashboard/SmartDashboard.h>

#include <iostream>
#include <stdio.h>

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

  _controller.SetP(frc::SmartDashboard::GetNumber("LimelightP", 0.0));
  _controller.SetI(frc::SmartDashboard::GetNumber("LimelightI", 0.0));
  _controller.SetD(frc::SmartDashboard::GetNumber("LimelightD", 0.0));
  _controllerF = frc::SmartDashboard::GetNumber("LimelightF", 0.0); //0.08

  double _output = _controller.Calculate(_subShooter->GetLimelight().tx, 0.0);
  if (_output > 0 + VisionToleranceLevel) {
    _output = _output + _controllerF;
    _subDriveBase->drive(0.0, _output, false);
  }
  else if (_output < 0 - VisionToleranceLevel) {
    _output = _output - _controllerF;
    _subDriveBase->drive(0.0, _output, false);
  }
  else {
    isFinished = true;
  }

}

// Called once the command ends or is interrupted.
void CmdTrackTarget::End(bool interrupted) {
  _subDriveBase->drive(0.0, 0.0, false);
}

// Returns true when the command should end.
bool CmdTrackTarget::IsFinished() {
  return isFinished;
}
