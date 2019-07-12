/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>
#include "Robot.h"
#include "frc/WPILib.h"
using namespace frc;

class CmdInspireArm : public frc::Command {
 public:
  CmdInspireArm();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
  double _angle;

  // These values will need to be changed (duh) - I wasn't at the robot to test this at the time of writing.
  enum ArmState {
    FLOOR = 0,
    HATCH = 0,
    SKY = 0,
    HAB = 0,
  };


 private:
  double kF; 
  double kP;
  double kI;
  double kD;

  double angle;

  double cruiseVelocity;
  double maxAcceleration;

  //feedforward multiplier
  double multiplier = 0.17;
  double angleRadians;
  double position;
};
