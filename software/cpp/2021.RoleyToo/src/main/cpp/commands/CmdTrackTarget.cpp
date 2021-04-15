// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdTrackTarget.h"
#include "frc/smartdashboard/SmartDashboard.h"


CmdTrackTarget::CmdTrackTarget(SubTurret* subTurret, SubIntake* subIntake) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subTurret = subTurret;
  _subIntake = subIntake;
  frc::SmartDashboard::PutNumber("Hood Target", 7.15);
  frc::SmartDashboard::PutNumber("Hood F", _hoodF);
}

// Called when the command is initially scheduled.
void CmdTrackTarget::Initialize() {
  frc::SmartDashboard::PutData("Turret PID", &_turretPID);
  frc::SmartDashboard::PutData("Hood PID", &_hoodPID);
  _subTurret->LimeLEDOn();
  _subIntake->Deploy();
}

// Called repeatedly when this Command is scheduled to run
void CmdTrackTarget::Execute() {
  //LEFT POSITIVE, RIGHT NEGATIVE
  _hoodF = frc::SmartDashboard::GetNumber("Hood F", 0);
  _hoodTarget = frc::SmartDashboard::GetNumber("Hood Target", 0);
  frc::SmartDashboard::PutNumber("Estimated Hood Angle", _subTurret->CalculateHoodAngle(_subTurret->GetY()));
  if (_subTurret->CheckTarget()) {
      _failureCount = 0;
      std::cout << "Target Visible\n";
      _TurretPIDOutput = std::clamp(_turretPID.Calculate(_subTurret->GetX()), -0.25, 0.25);
      //_hoodPIDOutput = std::clamp(_hoodPID.Calculate(_subTurret->GetHoodPos(), _subTurret->CalculateHoodAngle(_subTurret->GetY())), -0.5, 0.5);
      _hoodPIDOutput = std::clamp(_hoodPID.Calculate(_subTurret->GetHoodPos(), _hoodTarget), -0.5, 0.5);

  }
  else {
    _failureCount++;
    if (_failureCount > 20) {
      _TurretPIDOutput = std::clamp(_turretPID.Calculate(_subTurret->GetTurretAngle(), _turretCenterPoint), -0.25, 0.25);
      //_hoodPIDOutput = std::clamp(_hoodPID.Calculate(_subTurret->GetHoodPos(), 8.25), -0.5, 0.5);
      _hoodPIDOutput = std::clamp(_hoodPID.Calculate(_subTurret->GetHoodPos(), _hoodTarget), -0.5, 0.5);
    }
  }

  if ((_subTurret->GetTurretAngle() < _turretRightLimit) && (_TurretPIDOutput < 0)) { _TurretPIDOutput = 0; }     // Right Limit
  if ((_subTurret->GetTurretAngle() > _turretLeftLimit) && (_TurretPIDOutput > 0)) { _TurretPIDOutput = 0; }      // Left Limit

  if (_hoodPIDOutput < 0 && _subTurret->GetHoodLimit()) { _hoodPIDOutput = 0; }
  if (_hoodPIDOutput > 0 && _subTurret->GetHoodPos() > _hoodUpperLimit) { _hoodPIDOutput = 0; }

  std::cout << "Turret PID Output: " << _TurretPIDOutput;
  std::cout << "Hood PID Output: " << _hoodPIDOutput << "\n";
  _subTurret->SetTurret(_TurretPIDOutput);
  _subTurret->SetHood(_hoodPIDOutput);

  frc::SmartDashboard::PutNumber("Hood Angle", _subTurret->GetHoodPos());
}

// Called once the command ends or is interrupted.
void CmdTrackTarget::End(bool interrupted) {
  _subTurret->SetTurret(0);
  _subTurret->SetHood(0);
  _subTurret->LimeLEDOff();
  _subIntake->Retract();
}

// Returns true when the command should end.
bool CmdTrackTarget::IsFinished() {
  return false;
}
