#include "commands/CmdClimberLatch.h"
#include "Robot.h"

CmdClimberLatch::CmdClimberLatch() {
  Requires(Robot::subClimber.get());
}

void CmdClimberLatch::Initialize() {
  Robot::subClimber->Latch();
}

void CmdClimberLatch::Execute() {}
bool CmdClimberLatch::IsFinished() { return false; }

void CmdClimberLatch::End() {
  // Robot::subClimber->Unlatch();
}

void CmdClimberLatch::Interrupted() {}
