// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubColorWheel.h"
#include <frc/smartdashboard/smartdashboard.h>
#include <array>
#include <iostream>

SubColorWheel::SubColorWheel() = default;

// This method will be called once per scheduler run
void SubColorWheel::Periodic() {
  frc::Color detectedColor = _colorSensor.GetColor();
  double _red = detectedColor.red;
  double _green = detectedColor.green;
  double _blue = detectedColor.blue;

  std::array<Color, 4> colorArray {red, green, blue, yellow}; 
  for(Color currentColor : colorArray){
    double currentError = currentColor.GetError(_red, _green, _blue);
    if(smallestError > currentError){
      smallestError = currentError;
      smallestColor = currentColor;
    } 
  }

  frc::SmartDashboard::PutString("Color", smallestColor._name);
    
  smallestError = 1;
  smallestColor = Color{0, 0, 0, "None"};

  // frc::SmartDashboard::PutNumber("Red", detectedColor.red);
  // frc::SmartDashboard::PutNumber("Green", detectedColor.green);
  // frc::SmartDashboard::PutNumber("Blue", detectedColor.blue);
}
