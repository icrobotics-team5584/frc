// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"
#include <frc/smartdashboard/SmartDashboard.h>

void Robot::RobotInit() {
  AddPeriodic([this]{FastPeriodic();}, 5_ms);
  sparkMax.SetPeriodicFramePeriod(rev::CANSparkLowLevel::PeriodicFrame::kStatus4, 5); // Speed up readings of alternate encoder pos and velocity
  sparkMax.SetPeriodicFramePeriod(rev::CANSparkLowLevel::PeriodicFrame::kStatus3, 5); // Speed up readings of alternate encoder pos and velocity
  sparkAlternateEncoder.SetMeasurementPeriod(5);
}

void Robot::FastPeriodic() {
  // Digital Inputs
  frc::SmartDashboard::PutBoolean("digital/0", limitSwitch.Get());
  frc::SmartDashboard::PutBoolean("digital/1", reflector.Get());
  frc::SmartDashboard::PutBoolean("digital/2", lineBreak.Get());
  frc::SmartDashboard::PutBoolean("digital/3", reedSwitch.Get());

  // Colour Sensor
  auto sensedColour = colourSesnor.GetColor();
  frc::SmartDashboard::PutNumber("Colour/red", sensedColour.red); 
  frc::SmartDashboard::PutNumber("Colour/green", sensedColour.green);
  frc::SmartDashboard::PutNumber("Colour/blue", sensedColour.blue);
  frc::SmartDashboard::PutNumber("Colour/IR", colourSesnor.GetIR());
  frc::SmartDashboard::PutNumber("Colour/proximity", colourSesnor.GetProximity());

  // Gyro
  frc::SmartDashboard::PutNumber("gyro/pitch", navx.GetPitch());
  frc::SmartDashboard::PutNumber("gyro/roll", navx.GetRoll());
  frc::SmartDashboard::PutNumber("gyro/yaw", navx.GetYaw());
  frc::SmartDashboard::PutNumber("gyro/accel", navx.GetAccelFullScaleRangeG());

  // Encoders
  // frc::SmartDashboard::PutNumber("motors/SparkMax Encoder", sparkMax.GetPosition().value());
  frc::SmartDashboard::PutNumber("encoders/SparkMax Internal Encoder", sparkMax.GetPosition().value());
  frc::SmartDashboard::PutNumber("encoders/SparkFlex Internal Encoder", sparkFlex.GetPosition().value());
  frc::SmartDashboard::PutNumber("encoders/SparkMax Alternate Encoder", sparkAlternateEncoder.GetPosition());

  // Analog Input
  frc::SmartDashboard::PutNumber("analog/potentiometer", potentiometer.GetValue());
}

void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {
  if (!reedSwitch.Get()){
    if (!lineBreak.Get()) {
      sparkFlex.SetVoltage(potentiometer.GetVoltage()*2_V); // Faster
    } else {
      sparkFlex.SetVoltage(potentiometer.GetVoltage()*1_V); // Slower
    }
  } else {
    sparkFlex.SetVoltage(0_V);
  }

  if (!limitSwitch.Get()) {
    if (!reflector.Get()) {
      talon.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, sparkMax.GetVelocity().value() / 5.0); // inbuilt
    } else {
      talon.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, sparkAlternateEncoder.GetVelocity()/60.0 / 5.0); // alternate
    }
  } else {
    talon.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0);
  }
}

void Robot::DisabledInit() {
  sparkMax.SetVoltage(0_V);
  sparkFlex.SetVoltage(0_V);
  talon.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0);
}
void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}

void Robot::SimulationInit() {}
void Robot::SimulationPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
