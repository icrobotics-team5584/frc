// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/SubTurret.h"
#include <frc/controller/PIDController.h>

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class CmdSpinFlywheel : public frc2::CommandHelper<frc2::CommandBase, CmdSpinFlywheel> {
 public:
  CmdSpinFlywheel(SubTurret* subTurret);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;
 private:
  SubTurret* _subTurret;
  frc2::PIDController _flywheelPID{0.00005, 0.0, 0.0000053}; //default values
  double _PIDOutput = 0;
  double _maxPower = 1;
  double _setpoint = 5000;
  double _currentPower = 0;
  double _error = 0;
};
