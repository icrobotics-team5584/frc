/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include <frc/DigitalInput.h>


class SubStorage : public frc::Subsystem {
 private:
  const double kDefaultFeederSpeed = 0.8;
  double _speed = kDefaultFeederSpeed;
  std::shared_ptr<TalonSRX> srxStorage;

  frc::DigitalInput lbrTopStorage;
    
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities

 public:
  SubStorage();
  void InitDefaultCommand() override;
  bool GetLbrTopStorage();
  void Forward();
  void Backward();
  void Stop();
};
