// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>

#include "subsystems/SubDriveBase.h"
#include "commands/CmdAutoDrive.h"
#include "Utilities/PIDk.h"
#include "CmdAutoSetPose.h"
#include "commands/CmdAutoTurn.h"
#include "subsystems/SubIntake.h"
#include "subsystems/SubShooter.h"
#include "subsystems/SubStorage.h"

class Cmd2BallAutoNoDolly
    : public frc2::CommandHelper<frc2::SequentialCommandGroup,
                                 Cmd2BallAutoNoDolly> {
 public:
  Cmd2BallAutoNoDolly(SubDriveBase* subDriveBase, SubIntake* subIntake, SubShooter* subShooter, SubStorage* subStorage, Autonomous* autonomous);

 private:
  // Autonomous _autonomous;

};
