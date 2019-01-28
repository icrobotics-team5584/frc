/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>
#include <frc/Timer.h>


class CmdOutputPanel : public frc::Command {
  private:
  double timeoutTime = 0.3;
  bool _autoHold;
  bool notDeployed;
  frc::Timer _timer;
  public:
  CmdOutputPanel(bool autoHold);
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
};
