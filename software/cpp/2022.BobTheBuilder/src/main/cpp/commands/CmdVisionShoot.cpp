#include "commands/CmdVisionShoot.h"

CmdVisionShoot::CmdVisionShoot(SubShooter* subShooter) {
  _subShooter = subShooter;
}

void CmdVisionShoot::Initialize() {
}

void CmdVisionShoot::Execute() {
  double _e = _subShooter->GetVisionVelocityError();
  if (_e > _e-_thr or _e < _e+_thr) {
    _lock = true;
  }
}

void CmdVisionShoot::End(bool interrupted) {}

bool CmdVisionShoot::IsFinished() {
  return _lock;
}
