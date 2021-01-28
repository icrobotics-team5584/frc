// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdSpinFlywheel.h"

CmdSpinFlywheel::CmdSpinFlywheel(SubTurret* subTurret) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subTurret = subTurret;
}

// Called when the command is initially scheduled.
void CmdSpinFlywheel::Initialize() {
    frc::SmartDashboard::PutData("PID", &_flywheelPID);
    frc::SmartDashboard::PutNumber("Flywheel RPM", _flywheelRPM);
}

// Called repeatedly when this Command is scheduled to run
void CmdSpinFlywheel::Execute() {
  _flywheelRPM = frc::SmartDashboard::GetNumber("Flywheel RPM", 0);

  _PIDOutput = _flywheelPID.Calculate(_subTurret->GetFlywheelVelocity());

  _MotorSpeed += _PIDOutput;

  if (_MotorSpeed > 1) {
    _MotorSpeed = 1;
  }
  if (_MotorSpeed < 0) {
    _MotorSpeed = 0;
  }

  _subTurret->SetFlywheel(_MotorSpeed);
}

// Called once the command ends or is interrupted.
void CmdSpinFlywheel::End(bool interrupted) {
  _subTurret->SetFlywheel(0);
}

// Returns true when the command should end.
bool CmdSpinFlywheel::IsFinished() {
  return false;
}
