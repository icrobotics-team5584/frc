/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>
#include <frc/Timer.h>

enum State {WAITING_FOR_FINGERS_OUT, WAITING_FOR_BUTTON_RELEASE, WAITING_FOR_PUNCH_IN, FINISHED};

class CmdOutputPanel : public frc::Command {
private:
  const double FINGERS_WAIT_TIME = 0.3;
  const double PUNCH_WAIT_TIME = 0.2;
  frc::Timer timer;
  State state;

public:
  CmdOutputPanel();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
};
