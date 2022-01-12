// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/ParallelCommandGroup.h>

#include "subsystems/SubDriveBase.h"
#include "commands/CmdAutoDrive.h"
#include "Utilities/PIDk.h"

class Cmd2BallAuto
    : public frc2::CommandHelper<frc2::ParallelCommandGroup,
                                 Cmd2BallAuto> {
 public:
  Cmd2BallAuto(SubDriveBase* subDriveBase);

 private:
  Autonomous _autonomous;
};
