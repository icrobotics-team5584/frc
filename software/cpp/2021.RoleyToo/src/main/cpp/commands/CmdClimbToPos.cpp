// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdClimbToPos.h"
#include "subsystems/SubClimber.h"
#include "frc/smartdashboard/SmartDashboard.h"

CmdClimbToPos::CmdClimbToPos(SubClimber* subClimber, double target) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subClimber = subClimber;
  _target = target;
  
}

// Called when the command is initially scheduled.
void CmdClimbToPos::Initialize() {
  _climbPID.SetIntegratorRange(-1, 1);
  frc::SmartDashboard::PutData("ClimbPID", &_climbPID);
}

// Called repeatedly when this Command is scheduled to run
void CmdClimbToPos::Execute() {
  int _encoder = _subClimber->GetEncoder(SubClimber::Side::left);

  frc::SmartDashboard::PutNumber("climbencoder", _encoder);

  _pidOutput = _climbPID.Calculate(_encoder, _target);
  _subClimber->Retract(_pidOutput, SubClimber::left);
  _subClimber->Retract(_pidOutput, SubClimber::right);
}

// Called once the command ends or is interrupted.
void CmdClimbToPos::End(bool interrupted) {
  _subClimber->Retract(0.0, SubClimber::left);
  _subClimber->Retract(0.0, SubClimber::right);
}

// Returns true when the command should end.
bool CmdClimbToPos::IsFinished() {
  return false;
}
