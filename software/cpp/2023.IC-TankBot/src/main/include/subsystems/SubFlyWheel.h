// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include "utilities/ICSparkMax.h"
#include "Constants.h"

class SubFlyWheel : public frc2::SubsystemBase {
 public:

   static SubFlyWheel& GetInstance() {
    static SubFlyWheel inst;
    return inst;
  }

  void StartFlyWheel();
  void StopFlyWheel();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

 private:
 SubFlyWheel();
 ICSparkMax<> _FlyWheelMotor{canid::FlyWheelMotor, 10_A};
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
