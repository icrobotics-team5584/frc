// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>
#include <frc/SpeedControllerGroup.h>
#include <frc/DoubleSolenoid.h>
#include "Constants.h"

class SubClimber : public frc2::SubsystemBase {
 public:
  SubClimber();

  int GetEncoder(bool side);
  void Drive(double speed);
  void SetPneumatic(frc::DoubleSolenoid::Value value);


  

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  rev::CANSparkMax _spmClimbLeft{can::spmClimbLeft, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  rev::CANSparkMax _spmClimbRight{can::spmClimbRight, rev::CANSparkMaxLowLevel::MotorType::kBrushless};

  frc::DoubleSolenoid _solClimb{pcm::solClimbDeploy, pcm::solClimbRetract};
};
