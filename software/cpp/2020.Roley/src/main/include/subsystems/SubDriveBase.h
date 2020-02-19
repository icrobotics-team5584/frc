/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/drive/DifferentialDrive.h>
#include "frc/commands/Subsystem.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include <AHRS.h>
#include "Utilities/PosEncoderGyro.h"
#include <frc/DoubleSolenoid.h>
#include <rev/CANSparkMax.h>
#include <ctre/Phoenix.h>
#include "Utilities/EncoderTalon.h"

using namespace std;

class SubDriveBase : public frc::Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  EncoderTalon dollyTalon;
  
 public:
    
  shared_ptr<rev::CANSparkMax> _spmFrontLeft;
  shared_ptr<rev::CANSparkMax> _spmFrontRight;
  shared_ptr<rev::CANSparkMax> _spmBackLeft;
  shared_ptr<rev::CANSparkMax> _spmBackRight;

  shared_ptr<frc::DoubleSolenoid> solDollyAcuator;

  unique_ptr<frc::DifferentialDrive> DiffDrive;

  shared_ptr<AHRS> ahrsNavXGyro;

  //shared_ptr<WPI_TalonSRX> _srxAutoXAxis;

// Robot constants
  const double WHEEL_DIAMETER = 0.0508; // in meters (0.1016 for lofty)(0.1524 for dizzy) (0.0508 for dolly)
  const int ENCODER_TICS_PER_ROTATION = 4096; // 
  const double pi = 3.1415926535897932384626433832795028841971693993751;
  double metersPerRotation; // calculated in constructor
  
// PID Values
  double kP = -0.9;
  double kI = 0.00001;
  double kD = -42;
  double previousError;
  double intergral = 0;
  double AutoSpeed = 0.8;
  double autoYaw = 0;
  double _targetYaw;
  double position = 0;

  double y_kP = 0.8;
  double y_kI = 0;
  double y_kD = 0;
  double y_previousError;
  double y_intergral = 0;
  double y_position;
  double y_target;
  double y_error;


 public:
  SubDriveBase();
  void InitDefaultCommand() override;
  void drive(double speed, double rotation, bool squaredInputs = true);
  double getYaw();
  double getDistanceTravelled();
  void zeroEncoders();
  void autoEncoderDrive(double target, double P, double I, double D, double Speed, double TargetY, double TargetAOA);
  void resetYaw();
  void Periodic() override;
  bool isNavxCal();
  double getActualYaw();
  void setTargetYaw(double TargetYaw);
  void deployDolly();
  void retractDolly();
  double getJoystickY();
  double getJoystickX();
  void autoConfig();
  void teleConfig();
};
