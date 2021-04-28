// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>
#include <frc/SpeedControllerGroup.h>
#include <frc/DoubleSolenoid.h>
#include <frc/Solenoid.h>
#include <frc/DigitalInput.h>
#include "Constants.h"

class SubClimber : public frc2::SubsystemBase {
 public:
  SubClimber();

  enum Side {
    left = 0,
    right = 1
  };

  enum Limit {
    EndStop = 0
  };

  enum Solenoids {
    SDeploy = 3,
    SRetract = 0
  };

  bool GetLimit(Limit limit);
  int GetEncoder(Side side);
  void Retract(double speed, Side side);
  void SetPneumatic(int value);
  void SetMode(bool mode);


  

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  rev::CANSparkMax _spmClimbLeft{can::spmClimbLeft, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  rev::CANSparkMax _spmClimbRight{can::spmClimbRight, rev::CANSparkMaxLowLevel::MotorType::kBrushless};

  frc::DoubleSolenoid _solClimb{1, pcm::solClimbDeploy, pcm::solClimbRetract};

  frc::DigitalInput _lmtEndStop{dio::lmtClimbStop};

  rev::CANEncoder _leftEncoder{_spmClimbLeft.GetEncoder()};
  rev::CANEncoder _rightEncoder{_spmClimbRight.GetEncoder()};
};
