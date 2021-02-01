// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubColorWheel.h"
#include <frc/smartdashboard/smartdashboard.h>
#include <frc/DriverStation.h>
#include <array>
#include <iostream>
#include <map>

SubColorWheel::SubColorWheel(){
    // Reset PID
    _colorMotorPID.SetP(kP);
    _colorMotorPID.SetI(kI);
    _colorMotorPID.SetD(kD);

    frc::SmartDashboard::PutData("Color wheel pid", &_colorMotorPID);
}

void SubColorWheel::Periodic() {
  frc::SmartDashboard::PutNumber("Encoder valude", _colorMotorEncoder.GetPosition());
  frc::SmartDashboard::PutNumber("color wheel pid error", _colorMotorPID.GetPositionError());
  calculated = _colorMotorPID.Calculate(_colorMotorEncoder.GetPosition());  
}

void SubColorWheel::SpinColorWheel(double rotation){
  // double neededRotations = _colorMotorPID.GetSetpoint() + rotation;
  _colorMotorPID.SetSetpoint(rotation);
  _spmColorMotor.Set(calculated);
}

Color SubColorWheel::DetectSensorColor(){
  // Those values are used for calculating the nearest color with the targets above
  double smallestError = 1;
  Color smallestColor{0, 0, 0, "None"};
  
  // Gets the value form the color sensor
  frc::Color detectedColor = _colorSensor.GetColor();
  double _red = detectedColor.red;
  double _green = detectedColor.green;
  double _blue = detectedColor.blue;

  // Gets the lowest error percentage from the values detected from the sensor
  std::array<Color, 4> colorArray {red, green, blue, yellow}; 
  for(Color currentColor : colorArray){
      double currentError = currentColor.GetError(_red, _green, _blue);
      if(smallestError > currentError){
          smallestError = currentError;
          smallestColor = currentColor;
      } 
  }

  // Put the result got from the calculations above on shuffleboard
  frc::SmartDashboard::PutString("Color", smallestColor._name);

  return smallestColor;
}

void SubColorWheel::spinMotor(double speed){
  _spmColorMotor.Set(speed);
}

std::string SubColorWheel::GetWantedColor(){
  std::string gameData;
  gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
  if(gameData.length() > 0)
  {
    switch (gameData[0])
    {
      case 'B' :
        wantedColor = "Blue";
        break;
      case 'G' :
        wantedColor = "Green";
        break;
      case 'R' :
        wantedColor = "Red";
        break;
      case 'Y' :
        wantedColor = "Yellow";
        break;
      default :
        break;
    }
  }
  std::cout << ControlPanelColorMap[wantedColor] << std::endl;
  return ControlPanelColorMap[wantedColor];
}

bool SubColorWheel::CheckSetPoint(){
  return _colorMotorPID.AtSetpoint();
}

