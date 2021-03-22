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
  _PIDOutput = _flywheelPID.Calculate(_subTurret->GetFlywheelRPM(), _setpoint);
  //std::cout << "output: " << _PIDOutput << "\n";
  frc::SmartDashboard::PutNumber("current flywheel power", _PIDOutput);
  _subTurret->SetFlywheel(_PIDOutput);
}

// Called once the command ends or is interrupted.
void CmdSpinFlywheel::End(bool interrupted) {
  _subTurret->SetFlywheel(0);
}

// Returns true when the command should end.
bool CmdSpinFlywheel::IsFinished() {
  return false;
}
