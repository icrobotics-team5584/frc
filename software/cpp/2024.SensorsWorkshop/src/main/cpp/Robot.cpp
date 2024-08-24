// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"
#include <frc/smartdashboard/SmartDashboard.h>

void Robot::RobotInit() {}
void Robot::RobotPeriodic() {
  // Digital Inputs
  frc::SmartDashboard::PutBoolean("digital/0", dio0.Get());
  frc::SmartDashboard::PutBoolean("digital/1", dio1.Get());
  frc::SmartDashboard::PutBoolean("digital/2", dio2.Get());
  frc::SmartDashboard::PutBoolean("digital/3", dio3.Get());

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
  frc::SmartDashboard::PutNumber("motors/SparkMax Encoder", sparkMax.GetPosition().value());
  frc::SmartDashboard::PutNumber("motors/SparkFlex Encoder", sparkFlex.GetPosition().value());
  frc::SmartDashboard::PutNumber("encoders/SparkMax Alternate Encoder", sparkAlternateEncoder.GetPosition());

  // Analog Input
  frc::SmartDashboard::PutNumber("analog/potentiometer", potentiometer.GetValue());
}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {}

void Robot::DisabledInit() {}
void Robot::DisabledPeriodic() {
}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}

void Robot::SimulationInit() {}
void Robot::SimulationPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
