// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include <frc/controller/PIDController.h>

#include <networktables/NetworkTable.h>

#include "subsystems/SubDriveBase.h"
#include "subsystems/SubShooter.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class CmdTrackTarget
    : public frc2::CommandHelper<frc2::CommandBase, CmdTrackTarget> {
 public:
  CmdTrackTarget(SubDriveBase* subDriveBase, SubShooter* subShooter);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  double VisionToleranceLevel = 0.5;
  double _setpoint = 3.5;

  SubDriveBase* _subDriveBase;
  SubShooter* _subShooter;

  frc2::PIDController _controller{0.05,0,0.05};
  double _controllerF = 0.1;
  bool isFinished = false;
};
