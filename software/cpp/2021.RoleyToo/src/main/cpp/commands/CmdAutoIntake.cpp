// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdAutoIntake.h"

CmdAutoIntake::CmdAutoIntake(SubIntake* subIntake, double sTime, double sTime2) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(subIntake);
  _subIntake = subIntake;
  _sTime = sTime;
  _sTime2 = sTime2;
}

// Called when the command is initially scheduled.
void CmdAutoIntake::Initialize() {
  _timer.Reset();
  _timer.Start();
}

// Called repeatedly when this Command is scheduled to run
void CmdAutoIntake::Execute() {
  if (_timer.Get() > _sTime){
    _subIntake->Intake(1.0);
  }
}

// Called once the command ends or is interrupted.
void CmdAutoIntake::End(bool interrupted) {
  _subIntake->Intake(0);
}

// Returns true when the command should end.
bool CmdAutoIntake::IsFinished() {
  if (_timer.Get() > _sTime + _sTime2){
    _timer.Stop();
    return true;
  }else{
    return false;
  }
}
