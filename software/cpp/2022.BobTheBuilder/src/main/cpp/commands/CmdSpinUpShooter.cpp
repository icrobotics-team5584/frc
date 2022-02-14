// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdSpinUpShooter.h"

CmdSpinUpShooter::CmdSpinUpShooter(SubShooter* subShooter, int rpm) {
  // Use addRequirements() here to declare subsystem dependencies.
 _subShooter = subShooter;
 _rpm = rpm;
}

// Called when the command is initially scheduled.
void CmdSpinUpShooter::Initialize() {
  _subShooter->SetTargetRpm(_rpm);
}

// Called repeatedly when this Command is scheduled to run
void CmdSpinUpShooter::Execute() {}

// Called once the command ends or is interrupted.
void CmdSpinUpShooter::End(bool interrupted) {}

// Returns true when the command should end.
bool CmdSpinUpShooter::IsFinished() {

  if (_subShooter->IsAtTargetSpeed()){
    return true; }
  else
   {false;}
  
}
