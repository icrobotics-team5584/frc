/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include "frc/WPILib.h"
#include "subsystems/SubEncodedArm.h"

class armOutput : public frc::PIDOutput {
 public:
  armOutput();
 private:
  virtual void PIDWrite(double output);
  double _top = 3222;

  double _angle;
  double _angleDeg;
  double _angleRad;
  double pi = 3.14159265349;
  double _outputSpeed;
  double multiplier = 1;
};
