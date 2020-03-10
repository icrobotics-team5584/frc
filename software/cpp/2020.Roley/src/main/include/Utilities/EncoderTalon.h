/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include <ctre/Phoenix.h>

class EncoderTalon {
 public:
  EncoderTalon(TalonSRX *talon);
  double GetEncoderValue();
  void ResetEncoder();
 private:
  TalonSRX *_talon;
};
