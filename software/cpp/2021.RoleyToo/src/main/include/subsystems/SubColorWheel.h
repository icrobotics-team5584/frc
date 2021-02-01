// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <rev/ColorSensorV3.h>
#include <frc/controller/PIDController.h>
#include <map>
#include <string>
#include <stdlib.h>

#include "Utilities/sendableSparkMax.h"
#include "Constants.h"

struct Color{
  // The class initializer that takes the targeted color value
  Color(double red, double green, double blue, std::string name){
    _red = red;
    _blue = blue;
    _green = green;
    _name = name;
  }
  // GetError() takes detected rgb values and take the difference between 
  double GetError(double detectedRed, double detectedGreen, double detectedBlue){
    double sumError = 0;
    sumError += abs(detectedRed - _red);
    sumError += abs(detectedGreen - _green);
    sumError += abs(detectedBlue - _blue);
    return sumError;
  }

  std::string GetName(){return _name;}

  // Stored variables for the struct with rgb color value and the name of the string
  double _red;
  double _blue;
  double _green;
  std::string _name; 
};

class SubColorWheel : public frc2::SubsystemBase {
 public:
  std::map<std::string, std::string> RobotColorMap = {
      { "Yellow" , "Green"},
      { "Blue" , "Red" },
      { "Green" , "Yellow" },
      { "Red" , "Blue" }
  };

  std::map<std::string, std::string> ControlPanelColorMap = {
      { "Green", "Yellow"},
      { "Red" , "Blue"},
      { "Yellow" , "Green"},
      { "Blue" , "Red"}
  };

  SubColorWheel();
  void Periodic() override;

  // Takes speed and how many rotation the motor spins
  void SpinColorWheel(double rotation);

  Color DetectSensorColor();

  void spinMotor(double speed);

  std::string GetWantedColor();

  bool CheckSetPoint();
 private:
  rev::ColorSensorV3 _colorSensor{frc::I2C::Port::kOnboard};

  // Those values are the target value that should be changed depending on lighting enviorment
  Color blue{0.14, 0.44, 0.42, "Blue"};       // Target Blue Value
  Color green{0.18, 0.565, 0.253, "Green"};   // Target Green Value
  Color red{0.463, 0.38, 0.156, "Red"};       // Target Red Value
  Color yellow{0.31, 0.557, 0.133, "Yellow"}; // Target Yellow value

  double kP = 0.1, kI = 0, kD = 0, kMaxOutput = 0.5, kMinOutput = -0.5;
  
  // SparkMax motor controller for the motor that spins the color wheel
  rev::CANSparkMax _spmColorMotor{can::spmColorWheel, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANEncoder _colorMotorEncoder = _spmColorMotor.GetEncoder();
  frc2::PIDController _colorMotorPID{kP, kI, kD};
  double calculated = 0;

  std::string wantedColor;
};
