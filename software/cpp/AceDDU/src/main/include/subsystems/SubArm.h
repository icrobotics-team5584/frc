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

#include "commands/CmdPidArm.h"

class SubArm : public frc::Subsystem {
 private:
  CmdPidArm pidArm;
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities

 public:
  SubArm();
  void InitDefaultCommand() override;
  
  void Toggle();
  void Enable();
  void Disable();
  void SetSetpoint(double setpoint);
  void SetRelativeSetpoint(double setpoint);
  void ArmTo(int angle);
  void ArmJoyControl();
  double getAngle();
};
