// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/SubTurret.h"
#include "subsystems/SubStorage.h"
#include <frc/controller/PIDController.h>

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class CmdTrackTarget : public frc2::CommandHelper<frc2::CommandBase, CmdTrackTarget> {
 public:
  CmdTrackTarget(SubTurret* subTurret);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;
 private:
  SubTurret* _subTurret;
  SubStorage* _subStorage;

  double FlywheelRPMTarget = 5000;
  double FlywheelPID[3] = {0.01, 0.0, 0.0000053};

  frc2::PIDController _flywheelPID{FlywheelPID[0], FlywheelPID[1], FlywheelPID[2]};
  frc2::PIDController _turretPID{0.012, 0.0, 0.003}; //default values
  frc2::PIDController _hoodPID{0.4, 0.0, 0.0};
  double _hoodF = 0;

  int _failureCount = 0;
  double _TurretPIDOutput = 0;
  double _hoodPIDOutput = 0;
  double FlywheelPIDOutput;

  double _hoodError = 0;
  double _hoodTarget = 0;
  double _hoodUpperLimit = 11.3;
};
