/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>
#include "Robot.h"

enum DriveStateTypeR {SEARCHING, LINE_DETECTED, REVERSING_TO_LINE, RAISING_ELEVATOR, SHOOTING_CARGO};

class CmdSeekRocketCargo : public frc::Command {
 public:
  CmdSeekRocketCargo();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
 private:
  DriveStateTypeR driveStateRocket;
  double drivePower;
  double frontClsDetected;
  double midClsDetected;
  bool finishStage;
  double initialEncoderPos;
  double distance;
};
