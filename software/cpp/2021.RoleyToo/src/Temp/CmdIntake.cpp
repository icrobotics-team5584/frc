// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdIntake.h"
#include <frc/smartdashboard/SmartDashboard.h>

CmdIntake::CmdIntake(SubIntake* subIntake) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subIntake = subIntake;
}

// Called when the command is initially scheduled.
void CmdIntake::Initialize() {
  _timer.Reset();
  _timer.Start();
}

// Called repeatedly when this Command is scheduled to run
void CmdIntake::Execute() {
  _subIntake->Deploy();
  if(_timer.Get() > 1){_subIntake->Outtake();}
  else{_subIntake->Intake();}
}

// Called once the command ends or is interrupted.
void CmdIntake::End(bool interrupted) {
  std::cout << "running CmdIntake::End()" << std::endl;
  _subIntake->Stop();
  _subIntake->Retract();
}

// Returns true when the command should end.
bool CmdIntake::IsFinished() {
  return false;
}
