// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdTrackTarget.h"
#include "frc/smartdashboard/SmartDashboard.h"


CmdTrackTarget::CmdTrackTarget(SubTurret* subTurret, SubStorage* subStorage) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subTurret = subTurret;
  _subStorage = subStorage;
  frc::SmartDashboard::PutNumber("Hood Setpoint", 0);
  _subTurret->ResetHoodEncoder();

  frc::SmartDashboard::PutNumber("Turret P", 0.01);
  frc::SmartDashboard::PutNumber("Turret I", 0);
  frc::SmartDashboard::PutNumber("Turret D", 0.0000004);
  frc::SmartDashboard::PutNumber("Turret F", 0);
}

// Called when the command is initially scheduled.
void CmdTrackTarget::Initialize() {
  frc::SmartDashboard::PutData("Turret PID", &_turretPID);
  frc::SmartDashboard::PutData("Hood PID", &_hoodPID);
  _subTurret->LimeLEDOn();
}

// Called repeatedly when this Command is scheduled to run
void CmdTrackTarget::Execute() {

  _subStorage->Move(SubStorage::Forward, 0.80);
  _flywheelPID.SetPID(frc::SmartDashboard::GetNumber("Turret P", 0), frc::SmartDashboard::GetNumber("Turret I", 0), frc::SmartDashboard::GetNumber("Turret D", 0));
  FlywheelPIDOutput = _flywheelPID.Calculate(_subTurret->GetFlywheelRPM(), FlywheelRPMTarget);
  _subTurret->SetFlywheel(FlywheelPIDOutput + frc::SmartDashboard::GetNumber("Turret F", 0));
  //LEFT POSITIVE, RIGHT NEGATIVE
  if (_subTurret->CheckTarget()) {
      _failureCount = 0;
      std::cout << "Target Visible\n";
      frc::SmartDashboard::PutNumber("DIST", _subTurret->EstimateDistance());
      frc::SmartDashboard::PutNumber("HOOD", _subTurret->GetHoodPos());
      _TurretPIDOutput = std::clamp(_turretPID.Calculate(_subTurret->GetX()), -0.25, 0.25);
      _hoodPIDOutput = std::clamp(_hoodPID.Calculate(_subTurret->GetHoodPos(),frc::SmartDashboard::GetNumber("Hood Setpoint", 0)), -0.4, 0.4);
      _subTurret->SetReady(true);
  }
  else {
    _failureCount++;
    if (_failureCount > 20) {
      _TurretPIDOutput = 0;
      _hoodPIDOutput = 0;
      _subTurret->SetReady(false);
    }
  }

  //if ((_subTurret->GetTurretAngle() < 10) && (_TurretPIDOutput > 0)) { _TurretPIDOutput = 0; }
  //if ((_subTurret->GetTurretAngle() > 100) && (_TurretPIDOutput < 0)) { _TurretPIDOutput = 0; }

  //if ((_subTurret->GetHoodPos() < 10) && (_hoodPIDOutput < 0)) { _hoodPIDOutput = 0; }
  //if ((_subTurret->GetHoodPos() > 10) && (_hoodPIDOutput > 0)) { _hoodPIDOutput = 0; }

  std::cout << "Turret PID Output: " << _TurretPIDOutput;
  std::cout << "Hood PID Output: " << _hoodPIDOutput << "\n";
  //_subTurret->SetTurret(_TurretPIDOutput);
  if (_subTurret->GetHoodLimit() || _hoodPIDOutput < 0) {
    _subTurret->SetHood(_hoodPIDOutput);
  }
}

// Called once the command ends or is interrupted.
void CmdTrackTarget::End(bool interrupted) {
  _subStorage->Move(SubStorage::Forward, 0.0);
  _subTurret->SetFlywheel(0.0);
  _subTurret->SetReady(false);
  _subTurret->SetTurret(0);
  _subTurret->SetHood(0);
  _subTurret->LimeLEDOff();
}

// Returns true when the command should end.
bool CmdTrackTarget::IsFinished() {
  return false;
}
