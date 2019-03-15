#include "commands/CmdClimberDeploy.h"

CmdClimberDeploy::CmdClimberDeploy() {
  Requires(Robot::subClimber.get());
}

void CmdClimberDeploy::Initialize() {
  Robot::subClimber->Go();
}

void CmdClimberDeploy::Execute() {}

bool CmdClimberDeploy::IsFinished() { 
  return !Robot::_oi->btnClimber->Get();
}

void CmdClimberDeploy::End() {
  Robot::subClimber->Hold();
}

void CmdClimberDeploy::Interrupted() {
  End();
}
