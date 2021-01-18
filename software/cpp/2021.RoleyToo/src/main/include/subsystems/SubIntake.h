// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>
#include <frc/DoubleSolenoid.h>

#include "Constants.h"

class SubIntake : public frc2::SubsystemBase {
 public:
  SubIntake();  
  void Intake();
  void Outtake();
  void Deploy();
  void Retract();
  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  rev::CANSparkMax _spmIntake{can::spmIntake, rev::CANSparkMax::MotorType::kBrushless};
  frc::DoubleSolenoid solIntake{1, pcm::pcm_solIntakeRetract, pcm::pcm_solIntakeDeploy};

  const double kSpeed = 0.3; // Speed of the Intake

};
