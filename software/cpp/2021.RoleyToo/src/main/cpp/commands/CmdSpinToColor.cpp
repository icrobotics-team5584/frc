// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdSpinToColor.h"

CmdSpinToColor::CmdSpinToColor(SubColorWheel* subColorWheel){
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(subColorWheel);
  _subColorWheel = subColorWheel;
}

// Called when the command is initially scheduled.
void CmdSpinToColor::Initialize() {
  wantedColor = _subColorWheel->GetWantedColor();
  currentColor = _subColorWheel->DetectSensorColor();
}

// Called repeatedly when this Command is scheduled to run
void CmdSpinToColor::Execute() {
  currentColor = _subColorWheel->DetectSensorColor();
  _subColorWheel->spinMotor(0.2);
}

// Called once the command ends or is interrupted.
void CmdSpinToColor::End(bool interrupted) {
  _subColorWheel->spinMotor(0);
}

// Returns true when the command should end.
bool CmdSpinToColor::IsFinished() {
  return wantedColor == currentColor._name;
}
