/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <ctre/Phoenix.h>

class SubShooter : public frc::Subsystem {
 private:



  const int kTimeoutMs = 30;
  const int	kSlotIdx = 0;
  const int	kPIDLoopIdx = 0;



  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities

 public:
   std::shared_ptr<WPI_TalonSRX> leftMotor;
  std::shared_ptr<WPI_TalonSRX> rightMotor;
    double speed = 0.5;
  double GetLeftRPM();
  double GetRightRPM();
  SubShooter();
  void InitDefaultCommand() override;

  void Shoot();
  void Stop();
};
