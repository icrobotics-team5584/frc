// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdSpinColorWheel.h"

CmdSpinColorWheel::CmdSpinColorWheel(SubColorWheel* subColorWheel) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(subColorWheel);
  _subColorWheel = subColorWheel;
}

// Called when the command is initially scheduled.
void CmdSpinColorWheel::Initialize() {
  currentColor = _subColorWheel->DetectSensorColor();
  initialColor = currentColor.GetName();
}

// Called repeatedly when this Command is scheduled to run
void CmdSpinColorWheel::Execute() {
  currentColor = _subColorWheel->DetectSensorColor();
  _subColorWheel->spinMotor(0.1);
}

// Called once the command ends or is interrupted.
void CmdSpinColorWheel::End(bool interrupted) {
  _subColorWheel->spinMotor(0);
}

// Returns true when the command should end.
bool CmdSpinColorWheel::IsFinished() {
  return initialColor != currentColor._name;
}
