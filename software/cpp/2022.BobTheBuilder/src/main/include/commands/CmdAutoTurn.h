// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "subsystems/SubDriveBase.h"
#include "Utilities/Autonomous.h"
#include "Utilities/PIDk.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class CmdAutoTurn
    : public frc2::CommandHelper<frc2::CommandBase, CmdAutoTurn> {
 public:
  CmdAutoTurn(SubDriveBase* subDriveBase, Autonomous* autonomous, PIDk PIDconstants, double angle, double tolerance);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  DriveInput driveInput;
  SubDriveBase* _subDriveBase;
  Autonomous* _autonomous;
  PIDk _PIDconstants;
  double _tolerance;
  double _angle;
};
