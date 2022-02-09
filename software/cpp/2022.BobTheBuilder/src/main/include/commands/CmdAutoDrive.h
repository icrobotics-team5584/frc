// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "subsystems/SubDriveBase.h"
#include "Utilities/Autonomous.h"
#include "Utilities/PIDk.h"
#include "Utilities/AutoPIDConfig.h"
/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class CmdAutoDrive
    : public frc2::CommandHelper<frc2::CommandBase, CmdAutoDrive> {
 public:
  CmdAutoDrive(SubDriveBase* subDriveBase, Autonomous* autonomous, PIDAutoConfig _PIDConfig);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  DriveInput driveInput;
  SubDriveBase* _subDriveBase;
  Autonomous* _autonomous;

  double _startX;
  double _startY;
  double _endX;
  double _endY;
  double _endHeading;
  double _cenX;
  double _cenY;
  PIDk _PIDconstants;
  double _speed;
  double _endSpeed;
  PIDk _pidSpeed;
};
