#include "commands/CmdVisionShoot.h"

CmdVisionShoot::CmdVisionShoot(SubShooter* subShooter) {
  _subShooter = subShooter;
}

void CmdVisionShoot::Initialize() {}

void CmdVisionShoot::Execute() {}

void CmdVisionShoot::End(bool interrupted) {}

bool CmdVisionShoot::IsFinished() {
  return false;
}
