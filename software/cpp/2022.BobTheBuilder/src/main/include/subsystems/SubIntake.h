// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>
#include <frc/DoubleSolenoid.h>

class SubIntake : public frc2::SubsystemBase {
 public:
  SubIntake();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;
  void Intake();
  void Outtake();
  void Extend();
  void Retract();

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  rev::CANSparkMax _spmIntake{9, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
   frc::DoubleSolenoid _solPnuematics{0,frc::PneumaticsModuleType::CTREPCM,0,1};
};