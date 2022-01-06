// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/DoubleSolenoid.h>
#include "Constants.h"

class SubDrivebase : public frc2::SubsystemBase {
 public:
  SubDrivebase();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

  void Drive(double speed, double steering);
  void DollyDeploy();
  void DollyRetract();

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  rev::CANSparkMax frontLeft{4,  rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  rev::CANSparkMax frontRight{3, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  rev::CANSparkMax backLeft{2, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  rev::CANSparkMax backRight{1, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  frc::DifferentialDrive Diffdrive{frontLeft, frontRight};

  frc::DoubleSolenoid solDolly{1,pcm::solDollyDeploy,pcm::solDollyRetract};
  // this is a change
};
