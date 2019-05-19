#include "commands/CmdClimberRetract.h"
#include "Robot.h"

CmdClimberRetract::CmdClimberRetract() {
  Requires(Robot::subClimber.get());
}

void CmdClimberRetract::Initialize() {
  Robot::subClimber->Retract();
}

void CmdClimberRetract::Execute() {}

bool CmdClimberRetract::IsFinished() { 
  return !Robot::_oi->btnClimberRetract->Get();
}

void CmdClimberRetract::End() {
  Robot::subClimber->Stop();
}

void CmdClimberRetract::Interrupted() {}
