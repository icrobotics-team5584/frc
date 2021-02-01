// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdSpinFlywheel.h"

CmdSpinFlywheel::CmdSpinFlywheel(SubTurret* subTurret) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subTurret = subTurret;
  //#frc::SmartDashboard::PutNumber("Flywheel Max Power", _maxPower);
  //frc::SmartDashboard::PutNumber("Flywheel Setpoint", _setpoint);
}

// Called when the command is initially scheduled.
void CmdSpinFlywheel::Initialize() {
  frc::SmartDashboard::PutData("Wheel PID", &_flywheelPID);
}

// Called repeatedly when this Command is scheduled to run
void CmdSpinFlywheel::Execute() {
  _error = _subTurret->GetFlywheelRPM() - _setpoint;

  _setpoint = frc::SmartDashboard::GetNumber("wheel setpoint", 0);
  frc::SmartDashboard::PutNumber("wheel error", _error);
  _PIDOutput = _flywheelPID.Calculate(_error);
  _currentPower += _PIDOutput;
  //std::cout << "output: " << _PIDOutput << "\n";

  if (_currentPower > _maxPower) {
    _currentPower = _maxPower;
    //std::cout << "too fast" << "\n";
  }
  if (_currentPower < 0) {
    _currentPower = 0;
    //std::cout << "too slow" << "\n";
  }

  frc::SmartDashboard::PutNumber("current flywheel power", _currentPower);
  _subTurret->SetFlywheel(_currentPower);
}

// Called once the command ends or is interrupted.
void CmdSpinFlywheel::End(bool interrupted) {
  _subTurret->SetFlywheel(0);
}

// Returns true when the command should end.
bool CmdSpinFlywheel::IsFinished() {
  return false;
}
