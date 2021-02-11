// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>
#include "subsystems/SubDriveBase.h"
#include "commands/CmdAutoDrive.h"
#include "utilities/Autonomous.h"

class CmdAuto13Ball
    : public frc2::CommandHelper<frc2::SequentialCommandGroup,
                                 CmdAuto13Ball> {
 public:
  Autonomous _autonomous;
  CmdAuto13Ball(SubDriveBase* subDriveBase);
};
