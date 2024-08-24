// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/TimedRobot.h>
#include <frc/DigitalInput.h>
#include <rev/ColorSensorV3.h>
#include <AHRS.h>
#include <utilities/ICSparkMax.h>
#include <utilities/ICSparkFlex.h>
#include <ctre/phoenix/motorcontrol/can/TalonSRX.h>
#include <rev/SparkMaxAlternateEncoder.h>
#include <frc/AnalogInput.h>

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;

  void AutonomousInit() override;
  void AutonomousPeriodic() override;

  void TeleopInit() override;
  void TeleopPeriodic() override;

  void DisabledInit() override;
  void DisabledPeriodic() override;

  void TestInit() override;
  void TestPeriodic() override;

  void SimulationInit() override;
  void SimulationPeriodic() override;

  frc::DigitalInput dio0{0};
  frc::DigitalInput dio1{1};
  frc::DigitalInput dio2{2};
  frc::DigitalInput dio3{3};

  rev::ColorSensorV3 colourSesnor{frc::I2C::Port::kOnboard};

  AHRS navx{frc::SerialPort::Port::kUSB};

  ICSparkMax sparkMax{1, 20_A};
  ICSparkFlex sparkFlex{2, 20_A};
  ctre::phoenix::motorcontrol::can::TalonSRX talon{3};

  rev::SparkMaxAlternateEncoder sparkAlternateEncoder{sparkMax.GetAlternateEncoder(8192)};

  frc::AnalogInput potentiometer{0};
};
