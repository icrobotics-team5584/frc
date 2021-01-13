// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/Phoenix.h>
#include <frc/SpeedControllerGroup.h>
#include <frc/drive/DifferentialDrive.h>

#include "Constants.h"

class subDriveBase : public frc2::SubsystemBase {
 public:
  subDriveBase();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

  void Drive(double speed, double rotation);

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  
  WPI_VictorSPX spxFrontRight;
  WPI_VictorSPX spxFrontLeft;
  WPI_VictorSPX spxBackRight;
  WPI_VictorSPX spxBackLeft;

  frc::SpeedControllerGroup _spxLeftGroup{spxFrontLeft, spxBackLeft};
  frc::SpeedControllerGroup _spxRightGroup{spxFrontRight, spxBackRight};

  frc::DifferentialDrive DiffDrive{_spxLeftGroup, _spxRightGroup};

};
