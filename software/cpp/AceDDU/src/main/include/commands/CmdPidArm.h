/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/


#pragma once

#include<frc/WPILib.h>
#include <frc/commands/Command.h>
#include "PidsrcArm.h"

class CmdPidArm : public frc::Command {
 public:
  CmdPidArm(double position);
  std::shared_ptr<WPI_TalonSRX> srxShoulder;
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;

private: 
  double _position;
  frc::PIDController armController;
  PidsrcArm pidsrcArm;
};

