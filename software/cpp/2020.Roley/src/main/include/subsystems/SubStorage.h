/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/VictorSP.h>


class SubStorage : public frc::Subsystem {
 private:

  float speed = 0.8; 
  std::shared_ptr<frc::VictorSP> Motor;
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities

 public:
  SubStorage();
  void InitDefaultCommand() override;

  void Forward();
  void Backward();
  void Stop();
};