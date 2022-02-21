#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/SubShooter.h"

class CmdVisionShoot
    : public frc2::CommandHelper<frc2::CommandBase, CmdVisionShoot> {
 public:
  CmdVisionShoot(SubShooter* subShooter);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  SubShooter* _subShooter;
  
  double _thr = 3;
  double _lock = false;
};
