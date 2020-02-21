/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>

class CmdVisionTrack : public frc::Command {
 public:
  CmdVisionTrack();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
 private:
  double _speed = 0;
  double _cap = 0;
  double P = 0;
  double I = 0;
  double D = 0;
  double _error = 0;
  double _integral = 0;
  double _maxIntegral = 0;
  double _lastError = 0;
  double _derivative = 0;
};
