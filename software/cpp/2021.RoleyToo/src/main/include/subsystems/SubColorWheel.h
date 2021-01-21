// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <rev/ColorSensorV3.h>
#include <map>
#include <string>
#include <stdlib.h>

struct Color{
  Color(double red, double green, double blue, std::string name){
    _red = red;
    _blue = blue;
    _green = green;
    _name = name;
  }
  double GetError(double detectedRed, double detectedGreen, double detectedBlue){
    double sumError = 0;
    // std::cout << _name << sumError;
    // if(detectedRed > _red){sumError += (detectedRed - _red);}
    // else{sumError += (_red - detectedRed);}
    // std::cout << sumError;
    // if(detectedGreen > _green){sumError += (detectedGreen - _green);}
    // else{sumError += (_green - detectedGreen);}
    // std::cout << sumError;
    // if(detectedBlue > _blue){sumError += (detectedBlue - _blue);}
    // else{sumError += (_blue - detectedBlue);}
    // std::cout << sumError << std::endl;
    sumError += abs(detectedRed - _red);
    sumError += abs(detectedGreen - _green);
    sumError += abs(detectedBlue - _blue);
    return sumError;
  }
  double _red;
  double _blue;
  double _green;
  std::string _name; 
};

class SubColorWheel : public frc2::SubsystemBase {
 public:
  SubColorWheel();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

 private:
  rev::ColorSensorV3 _colorSensor{frc::I2C::Port::kOnboard};

  Color blue{0.14, 0.44, 0.42, "Blue"};
  Color green{0.18, 0.565, 0.253, "Green"};
  Color red{0.463, 0.38, 0.156, "Red"};
  Color yellow{0.31, 0.557, 0.133, "Yellow"};
  

  double smallestError = 1;
  Color smallestColor{0, 0, 0, "None"};
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
