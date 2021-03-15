// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/DoubleSolenoid.h>
#include <rev/CANSparkMax.h>
#include <rev/CANEncoder.h>
#include <AHRS.h>
#include "Constants.h"
#include "ctre/phoenix/motorcontrol/can/TalonSRX.h"

class SubDriveBase : public frc2::SubsystemBase {
 public:
  SubDriveBase();
  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void drive(double speed, double rotation, bool squaredInputs = false);
  void Periodic() override;
  void deployDolly();
  void retractDolly();
  void zeroEncoders();
  double getDistanceTravelled();
  void resetYaw();
  double getYaw();
  bool isNavxCal();
 
 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  rev::CANSparkMax _spmFrontLeft{can::spmDriveBaseFrontLeft, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax _spmFrontRight{can::spmDriveBaseFrontRight, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax _spmBackLeft{can::spmDriveBaseBackLeft, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax _spmBackRight{can::spmDriveBaseBackRight, rev::CANSparkMax::MotorType::kBrushless};
  ctre::phoenix::motorcontrol::can::TalonSRX _srxDolly{can::srxDolly};
  frc::DifferentialDrive _diffDrive{_spmFrontLeft, _spmFrontRight};

  const double WHEEL_DIAMETER = 0.0508; //0.0508 for dolly
  const int ENCODER_TICS_PER_ROTATION = 4096; 
  const double pi = 3.1415926535897932384626433832795028841971693993751;
  double metersPerRotation; // calculated in constructor

  frc::DoubleSolenoid solDollyAcuator{pcm::solDollyDeploy, pcm::solDollyRetract};
  AHRS ahrsNavXGyro{frc::SPI::kMXP};
};
