/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include "frc/WPILib.h"
#include <ctre/phoenix.h>
#include <frc/SmartDashboard/SmartDashboard.h>
#include <iostream>

class SubEncodedArm : public frc::Subsystem {
 private:
  //armPID* _armOutputPID;
  std::shared_ptr<frc::DoubleSolenoid> pneuBrake;

  double _angle;
  double _top = 3222;
  double _angleDeg;
  
  void configTalon();
 public:

  enum PneuBrakeState {
    BRAKE,
    COAST
  };

  SubEncodedArm();
  void InitDefaultCommand() override;
  int getEncoder();
  double getAngle();
  void setSpeed(double speed);
  void ResetEncoder();
  void BrakeState(PneuBrakeState brakeState);
  void SetAngle(double angle);
  void ConfigTalon();
  void SetPosition(double angle);

  std::shared_ptr<WPI_TalonSRX> srxArmFront;
	std::shared_ptr<WPI_TalonSRX> srxArmBack;
};
