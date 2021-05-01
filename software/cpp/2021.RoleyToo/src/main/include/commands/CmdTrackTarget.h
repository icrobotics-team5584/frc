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
  CmdTrackTarget(SubTurret* subTurret, SubStorage* subStorage,  double turretSetpoint = 9999999, double hoodSetpoint = 9999999);

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
  frc2::PIDController _turretPIDEncoder{0.06, 0.0, 0.003}; //default values
  frc2::PIDController _hoodPID{0.4, 0.0, 0.0};
  double _hoodF = 0;

  double _hoodDefaultAngle = 10;

  double _targetX = 0;

  int _failureCount = 0;
  double _TurretPIDOutput = 0;
  double _hoodPIDOutput = 0;
  double FlywheelPIDOutput;

  double _hoodError = 0;
  double _hoodTarget = 0;
  double _hoodUpperLimit = 14;

  double _turretLeftLimit = 30;
  double _turretRightLimit = -36;
  double _turretCenterPoint = 0;

  double _leftOffset = 1.5;     // Offset from the left to get balls to hit the center of the goal rather than veering off to the right
  double _rightOffset = 1.5;

  bool _overrideHood = false;
  bool _overrideTurret = false;
  double _overrideHoodTarget = 0;
  double _overrideTurretTarget = 0;

  double _hoodAngleOffset = 1.2;
};
