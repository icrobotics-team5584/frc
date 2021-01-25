// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdTrackTarget.h"
#include "frc/smartdashboard/SmartDashboard.h"


CmdTrackTarget::CmdTrackTarget(SubTurret* subTurret) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subTurret = subTurret;
}

// Called when the command is initially scheduled.
void CmdTrackTarget::Initialize() {
  frc::SmartDashboard::PutData("PID", &_turretPID);
  _subTurret->LimeLEDOn();
}

// Called repeatedly when this Command is scheduled to run
void CmdTrackTarget::Execute() {
  //LEFT POSITIVE, RIGHT NEGATIVE

  if (_subTurret->CheckTarget()) {
    _failureCount = 0;
    _PIDOutput = _turretPID.Calculate(_subTurret->GetX());
  }
  else {
    _failureCount++;
    if (_failureCount > 35) {
      _PIDOutput = _turretPID.Calculate(40 - _subTurret->GetTurretAngle());
    }
  }

  if ((_subTurret->GetTurretAngle() < 10) && (_PIDOutput > 0)) { _PIDOutput = 0; }
  if ((_subTurret->GetTurretAngle() > 100) && (_PIDOutput < 0)) { _PIDOutput = 0; }

  _subTurret->SetTurret(_PIDOutput);
}

// Called once the command ends or is interrupted.
void CmdTrackTarget::End(bool interrupted) {
  _subTurret->SetTurret(0);
  _subTurret->LimeLEDOff();
}

// Returns true when the command should end.
bool CmdTrackTarget::IsFinished() {
  return false;
}
