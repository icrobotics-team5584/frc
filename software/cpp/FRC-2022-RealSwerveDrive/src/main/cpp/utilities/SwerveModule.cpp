// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "utilities/SwerveModule.h"
#include <stdio.h>
#include <iostream>
#include <frc/smartdashboard/SmartDashboard.h>

SwerveModule::SwerveModule(int canDriveMotorID, int canTurnMotorID, int canTurnEncoderID, float magOffset) : 
  _canDriveMotor(canDriveMotorID),
  _canTurnMotor(canTurnMotorID),
  _canTurnEncoder(canTurnEncoderID)
{
  m_turningPIDController.EnableContinuousInput(
    -units::radian_t(wpi::numbers::pi), units::radian_t(wpi::numbers::pi));
  _canTurnEncoder.SetPositionToAbsolute();
  _canTurnEncoder.ConfigAbsoluteSensorRange(ctre::phoenix::sensors::AbsoluteSensorRange::Signed_PlusMinus180);
  _canTurnEncoder.ConfigMagnetOffset(magOffset);

  frc::SmartDashboard::PutNumber("TurnPID_P", 0);
  frc::SmartDashboard::PutNumber("TurnPID_I", 0);
  frc::SmartDashboard::PutNumber("TurnPID_D", 0);
  frc::SmartDashboard::PutNumber("TurnPID_F", 0);

}

frc::SwerveModuleState SwerveModule::GetState() {
  frc::SmartDashboard::PutNumber("AbsPos", _canTurnEncoder.GetAbsolutePosition());
  return {units::meters_per_second_t{_canDriveMotor.GetSelectedSensorVelocity(0)*kRotationConversion},
          frc::Rotation2d(units::radian_t(_canTurnEncoder.GetAbsolutePosition()*wpi::numbers::pi/180))};
}

void SwerveModule::SetDesiredState(
    const frc::SwerveModuleState& referenceState) {
  // Optimize the reference state to avoid spinning further than 90 degrees
  // const auto state = frc::SwerveModuleState::Optimize(
  //     referenceState, units::radian_t(_canTurnEncoder.GetAbsolutePosition()*wpi::numbers::pi/180));
  const auto state = referenceState;

  frc::SmartDashboard::PutNumber("ReferenceAngle", referenceState.angle.Degrees().value());
  frc::SmartDashboard::PutNumber("OptimisedAngle", state.angle.Degrees().value());

  double pid_p = frc::SmartDashboard::GetNumber("TurnPID_P", 0);
  double pid_i = frc::SmartDashboard::GetNumber("TurnPID_I", 0);
  double pid_d = frc::SmartDashboard::GetNumber("TurnPID_D", 0);
  double pid_f = frc::SmartDashboard::GetNumber("TurnPID_F", 0);

  m_turningPIDController.SetP(pid_p);
  m_turningPIDController.SetI(pid_i);
  m_turningPIDController.SetD(pid_d);

  // Calculate the drive output from the drive PID controller.
  const auto driveOutput = m_drivePIDController.Calculate(
      _canDriveMotor.GetSelectedSensorVelocity()*kRotationConversion, state.speed.value());

  const auto driveFeedforward = m_driveFeedforward.Calculate(state.speed);

  // Calculate the turning motor output from the turning PID controller.
  const auto turnOutput = m_turningPIDController.Calculate(
      units::degree_t(_canTurnEncoder.GetAbsolutePosition()), state.angle.Degrees());
  frc::SmartDashboard::PutNumber("PID Output", turnOutput);
  
  // const auto turnFeedforward = m_turnFeedforward.Calculate(
  //     m_turningPIDController.GetSetpoint().velocity);

  // Set the motor outputs.
  _canDriveMotor.Set(ctre::phoenix::motorcontrol::TalonFXControlMode::PercentOutput, (driveOutput + (double) driveFeedforward));
  _canTurnMotor.Set(ctre::phoenix::motorcontrol::TalonFXControlMode::PercentOutput, (turnOutput + pid_f));
}