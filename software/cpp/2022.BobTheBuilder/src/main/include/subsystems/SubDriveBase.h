// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>
#include <frc/drive/DifferentialDrive.h>
#include <AHRS.h>

#include "Constants.h"

class SubDriveBase : public frc2::SubsystemBase {
 public:
  // squaredInputs: 
  // If set, overrides constant-curvature turning for turn-in-place maneuvers. zRotation will control turning rate instead of curvature.
  SubDriveBase();

  void drive(double speed, double rotation, bool squaredInputs = false);

  // Create instances of motor controllers
  rev::CANSparkMax _spmFrontLeft{can::spmDriveBaseFrontLeft, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax _spmFrontRight{can::spmDriveBaseFrontRight, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax _spmBackLeft{can::spmDriveBaseBackLeft, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax _spmBackRight{can::spmDriveBaseBackRight, rev::CANSparkMax::MotorType::kBrushless};
  frc::DifferentialDrive _diffDrive{_spmFrontLeft, _spmFrontRight};

  void Periodic() override;

  double getYaw();
  bool isNavxCal();
  double getDistanceTravelled();

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  rev::SparkMaxRelativeEncoder _dollyWheel = _spmFrontLeft.GetEncoder();
  AHRS ahrsNavXGyro{frc::SPI::kMXP};

  double metersPerRotation; // calculated in constructor

  const double WHEEL_DIAMETER = 0.0508; //0.0508 for dolly
   
  const double pi = 3.1415926535897932384626433832795028841971693993751;
};
