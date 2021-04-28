// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdDeployClimber.h"
#include <Utilities/GameTimer.h>
#include "Constants.h"

CmdDeployClimber::CmdDeployClimber(SubClimber* subClimber) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subClimber = subClimber;
}

// Called when the command is initially scheduled.
void CmdDeployClimber::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void CmdDeployClimber::Execute() {

  // if (HasDeployed == false) {
  //   if (GameTimer::GetInstance()->GetTime(GameTimer::Seconds) < 30) {
  //     _subClimber->SetPneumatic(SubClimber::Solenoids::Deploy, frc::DoubleSolenoid::Value::kForward);
  //     HasDeployed = true;
  //   }
  // }
  // _subClimber->SetPneumatic(0); // 1= reverse, 2= forward, 0= off
  _subClimber->Retract(-0.8, SubClimber::left);
  _subClimber->Retract(-0.8, SubClimber::right);

}

// Called once the command ends or is interrupted.
void CmdDeployClimber::End(bool interrupted) {
  _subClimber->Retract(0, SubClimber::left);
  _subClimber->Retract(0, SubClimber::right);
}

// Returns true when the command should end.
bool CmdDeployClimber::IsFinished() {
  return false;
}
