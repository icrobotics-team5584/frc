/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>
#include "Robot.h"
#include <frc/Timer.h>

enum State { NORMAL, SHUFFLE, };

class CmdIntake : public frc::Command {
 public:
  CmdIntake();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
 private:
  void Intake();
  void Shuffle();
  double startTime = 0;
  frc::Timer timer;
  State currentState;
};
