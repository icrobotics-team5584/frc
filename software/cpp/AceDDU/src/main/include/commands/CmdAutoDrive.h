/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include<frc/WPILib.h>
#include <frc/commands/Command.h>
#include"PidsrcDistance.h"
#include "PidOutDistance.h"

class CmdAutoDrive : public frc::Command {
public:
  CmdAutoDrive(double distance);
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
  
private:
  frc::PIDController distanceController;
  PidsrcDistance pidsrcDistance;
  PidOutDistance pidOutDistance;
  double _distance;
  double _speed;
};


