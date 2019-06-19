/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/WPILib.h>

#include <frc/commands/Subsystem.h>
#include <ctre/Phoenix.h>

class SubIntake : public frc::Subsystem {
 private:
  const double SPEED = 0.5;

  std::shared_ptr<frc::DoubleSolenoid> SolMode;
  std::shared_ptr<WPI_TalonSRX> Motor;

 public:
  SubIntake();
  void InitDefaultCommand() override;
  //func
  void Intake();
  void Outtake();
  void Stop();
  void CargoMode();
  void HatchMode();
};
