// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/drive/DifferentialDrive.h>
#include <ctre/Phoenix.h>
#include "Constants.h"

class SubDriveBase : public frc2::SubsystemBase {
 public:
   static SubDriveBase &GetInstance() {static SubDriveBase inst; return inst;}

  void drive(double speed, double rotation, bool squaredInputs = false);

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

 private:
 SubDriveBase();
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
ctre::phoenix::motorcontrol::can::WPI_VictorSPX	_vspxLeftDriveMain{canid::LeftDriveMain};
ctre::phoenix::motorcontrol::can::WPI_VictorSPX	_vspxLeftDriveFollower{canid::LeftDriveFollower};
ctre::phoenix::motorcontrol::can::WPI_VictorSPX	_vspxRightDriveMain{canid::RightDriveMain};
ctre::phoenix::motorcontrol::can::WPI_VictorSPX	_vspxRightDriveFollower{canid::RightDriveFollower};

 frc::DifferentialDrive _diffDrive{_vspxLeftDriveMain, _vspxRightDriveMain};
};
