/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>
#include <fstream>
#include <frc/WPILib.h>

class CmdFindDtData : public frc::Command {
 public:
  CmdFindDtData();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
 private:
  std::ofstream file;
  frc::Timer timer;

  double currentTime;
  double oldTime = 0;

  double currentDisplacement;
  double oldDisplacement = 0;

  double currentVelocity;
  double oldVelocity = 0;

  double currentAcceleration;
  double oldAcceleration = 0;

  double jerk;
};
