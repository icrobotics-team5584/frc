// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <ctre/phoenix/sensors/CANCoder.h>
#include <ctre/phoenix/motorcontrol/can/TalonFX.h>
#include <frc/controller/PIDController.h>
#include <frc/controller/ProfiledPIDController.h>
#include <frc/controller/SimpleMotorFeedforward.h>
#include <frc/kinematics/SwerveModuleState.h>
#include <frc/motorcontrol/PWMSparkMax.h>
#include <units/angular_velocity.h>
#include <units/time.h>
#include <units/velocity.h>
#include <units/voltage.h>
#include <wpi/numbers>

class SwerveModule {
 public:
  SwerveModule(int canDriveMotorID, int canTurnMotorID, int canTurnEncoderID, float magOffset);

  frc::SwerveModuleState GetState();
  void SetDesiredState(const frc::SwerveModuleState& state);

 private:
  ctre::phoenix::motorcontrol::can::TalonFX _canDriveMotor;
  ctre::phoenix::motorcontrol::can::TalonFX _canTurnMotor;

  ctre::phoenix::sensors::CANCoder _canTurnEncoder;

  static constexpr auto kModuleMaxAngularVelocity =
      wpi::numbers::pi * 1_rad_per_s;  // radians per second
  static constexpr auto kModuleMaxAngularAcceleration =
      wpi::numbers::pi * 2_rad_per_s / 1_s;  // radians per second^2
  static constexpr double kRotationConversion = 10/2048/6.71*wpi::numbers::pi*0.1016;

  frc2::PIDController m_drivePIDController{1.0, 0, 0};
  frc::ProfiledPIDController<units::radians> m_turningPIDController{
      0.2,
      0.0,
      0.1,
      {kModuleMaxAngularVelocity, kModuleMaxAngularAcceleration}};
  
  frc::SimpleMotorFeedforward<units::meters> m_driveFeedforward{1_V,
                                                                3_V / 1_mps};
  frc::SimpleMotorFeedforward<units::radians> m_turnFeedforward{
      1_V, 0.5_V / 1_rad_per_s};

};
