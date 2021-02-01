// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <rev/CANSparkMax.h>
#include <frc/controller/PIDController.h>

#include "subsystems/SubClimber.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class CmdClimbToPos
    : public frc2::CommandHelper<frc2::CommandBase, CmdClimbToPos> {
 public:
  CmdClimbToPos(SubClimber* subClimber, double target);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;
 private:
  frc2::PIDController _climbPID{0.02, 0.0, 0.0};
  SubClimber* _subClimber;

  int _pidOutput = 0;
};
