// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include "utilities/ICSparkMax.h"
#include "Constants.h"

class SubIndexer : public frc2::SubsystemBase {
 public:
 
   static SubIndexer& GetInstance() {
    static SubIndexer inst;
    return inst;
  }


 void StartIndex();
 void StopIndex();
  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

 private:
SubIndexer();
ICSparkMax<> _IndexMotor{canid::IndexerMotor, 10_A};

  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
