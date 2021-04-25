// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc/controller/PIDController.h>

#include "subsystems/SubTurret.h"
#include "subsystems/SubIntake.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class CmdHomeTurret
    : public frc2::CommandHelper<frc2::CommandBase, CmdHomeTurret> {
 public:
  CmdHomeTurret(SubTurret* subTurret);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;
 private:
  SubTurret* _subTurret;
  frc2::PIDController _turretPID{0.06, 0.0, 0.003}; //default values

  double _homingSpeed = -0.1;

  int _state = 0;
};
