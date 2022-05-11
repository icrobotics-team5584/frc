// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/DoubleSolenoid.h>
#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>
#include <frc/DoubleSolenoid.h>
#include "Constants.h"
#include <frc/Timer.h>
#include <rev/ColorSensorV3.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include "frc/shuffleboard/Shuffleboard.h"
#include <frc/shuffleboard/SuppliedValueWidget.h>
#include <networktables/NetworkTableEntry.h>
#include "wpi/StringMap.h"

class SubStorage : public frc2::SubsystemBase {
 public:
  SubStorage();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;
  void In();
  void Stop();
  void DelayStop();
  void Out();
  void ExtendStopper();
  void RetractStopper();
  frc::Color DetectFrontBall();
  frc::Color DetectBackBall();
  frc::Timer timer;

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  rev::CANSparkMax _spmStorage{can::spmStorage,
                               rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  frc::DoubleSolenoid _solStopper{1, frc::PneumaticsModuleType::CTREPCM, pcm::solStorageStopperForward, pcm::solStorageStopperReverse};

  static constexpr auto i2cPortOnBoard = frc::I2C::Port::kOnboard;
  rev::ColorSensorV3 m_colorSensorFront{i2cPortOnBoard};

  static constexpr auto i2cPortMXP = frc::I2C::Port::kMXP;
  rev::ColorSensorV3 m_colorSensorBack{i2cPortMXP};

  frc::SuppliedValueWidget<bool>* _frontSensorWidget =
      &frc::Shuffleboard::GetTab("Sensors").AddBoolean("frontColorSensor",
                                                       [] { return true; });
  frc::SuppliedValueWidget<bool>* _backSensorWidget =
      &frc::Shuffleboard::GetTab("Sensors").AddBoolean("backColorSensor",
                                                       [] { return true; });

  wpi::StringMap<std::shared_ptr<nt::Value>> _frontColorDisplayProperties;
  wpi::StringMap<std::shared_ptr<nt::Value>> _backColorDisplayProperties;

  const std::shared_ptr<nt::Value> _blueName = nt::Value::MakeString("Blue");
  const std::shared_ptr<nt::Value> _redName = nt::Value::MakeString("Red");
  const std::shared_ptr<nt::Value> _greyName = nt::Value::MakeString("Grey");
  };
