/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>
#include "Robot.h"
#include "subsystems/SubElevator.h"
class CmdElevatorToPosition : public frc::Command {
 private:
 Heights _height = BOTTOM_CARGO;
 bool bottom = true;
 bool goTo;
 int setTo;
 int timeRound = 0;
 public:
  CmdElevatorToPosition(bool bottom1, bool goTo, int setTo);
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
};
