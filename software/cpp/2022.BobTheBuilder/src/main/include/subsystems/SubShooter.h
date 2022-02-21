// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>
#include <frc/DoubleSolenoid.h>
#include <frc/controller/PIDController.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/shuffleboard/Shuffleboard.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableEntry.h>
#include <networktables/NetworkTableInstance.h>

#include "Constants.h"

class LimelightData {
  public:
    LimelightData(double _tx, double _ty, double _thor, double _tvert) {
      tx = _tx;
      ty = _ty;
      thor = _thor;
      tvert = _tvert;
    }
    
    double tx;
    double ty;
    double thor;
    double tvert;
  };

class SubShooter : public frc2::SubsystemBase {
 friend LimelightData;
 public:
  SubShooter();
  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;
  void SetTargetRpm(int rpm);
  void Stop();
  bool IsAtTargetSpeed();
  LimelightData GetLimelight();
  void UpdatePidController();

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  rev::CANSparkMax _spmShooter1{can::spmShooter1, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  rev::CANSparkMax _spmShooter2{can::spmShooter2, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  rev::SparkMaxRelativeEncoder _encShooter1{_spmShooter1.GetEncoder()};
  frc2::PIDController _controller{0.001,0,0.00008};
  double _controllerF = 0;
  nt::NetworkTableInstance _inst;
  std::shared_ptr<nt::NetworkTable> _table;  
  nt::NetworkTableEntry _tx;
  nt::NetworkTableEntry _ty;
  nt::NetworkTableEntry _thor;
  nt::NetworkTableEntry _tvert;

};
