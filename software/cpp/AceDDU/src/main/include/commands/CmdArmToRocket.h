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

class CmdArmToRocket : public frc::Command {
 public:
  CmdArmToRocket();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
  
  static const double angle;

 private:
  double kF; 
  double kP;
  double kI;
  double kD;


  double cruiseVelocity;
  double maxAcceleration;
};
