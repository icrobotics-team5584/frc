/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include <frc/WPILib.h>

class CmdPidArm : public frc::PIDSubsystem {
 public:
  CmdPidArm();
  std::shared_ptr<WPI_TalonSRX> srxArm;
  double ReturnPIDInput() override;
  void UsePIDOutput(double output) override;
  void InitDefaultCommand() override;
 private:
  int _talon = 5; // arm talon number
};
