// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>
#include <frc/drive/DifferentialDrive.h>
#include <AHRS.h>
#include "ctre/Phoenix.h"

#include "Constants.h"

class SubDriveBase : public frc2::SubsystemBase {
 public:
  // squaredInputs: 
  // If set, overrides constant-curvature turning for turn-in-place maneuvers. zRotation will control turning rate instead of curvature.
  SubDriveBase();

  void drive(double speed, double rotation, bool squaredInputs = false);
  
  double GetTalonDistanceTravelled();

  TalonSRX _talonDolly{10};

  // Create instances of motor controllers
  rev::CANSparkMax _spmFrontLeft{4, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax _spmFrontRight{3, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax _spmBackLeft{2, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax _spmBackRight{1, rev::CANSparkMax::MotorType::kBrushless};
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

  const int ENCODER_TICS_PER_ROTATION = 4096;
   
  const double pi = 3.1415926535897932384626433832795028841971693993751;
};
