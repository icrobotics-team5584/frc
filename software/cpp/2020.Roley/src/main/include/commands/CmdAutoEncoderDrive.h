/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>
#include "Utilities/PosEncoderGyro.h"

class CmdAutoEncoderDrive : public frc::Command {
 public:
  CmdAutoEncoderDrive(double target, double P, double I, double D, double Speed, double TargetY);
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
 private:
  double _target = 0;
  double _P = 0;
  double _I = 0;
  double _D = 0;
  double _Speed  = 0;
  double _TargetY = 0;
  bool isForward;
};
