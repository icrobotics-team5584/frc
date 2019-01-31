/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>
#include "purePursuit/include/pathFollower.hpp"
#include "purePursuit/include/PosEncoderGyro.h"
#include "purePursuit/include/DvoTank.h"

class CmdSeekPath : public frc::Command {
 private:
  unique_ptr<PathFollower> pathFollower;
  shared_ptr<PosEncoderGyro> posEncoderGyro;
  shared_ptr<DvoTank> dvoTank;

  const double  wheelCircumference = 0.47877872; //(m)
  double scaleFactor;

 public:
  CmdSeekPath();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
};
