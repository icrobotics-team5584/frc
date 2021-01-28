// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "utilities/Autonomous.h"
#include "RobotContainer.h"
#include <math.h>
#include <frc/smartdashboard/SmartDashboard.h>
Autonomous::Autonomous(std::function<double()> getYaw, std::function<double()> getDistance){
  _getYaw = getYaw;
  _getDistance = getDistance;
  prevDistance = _getDistance();
  notifier.StartPeriodic(fasterPeriod);
}

void Autonomous::Periodic(){
  updatePosition();
  frc::SmartDashboard::PutNumber("x", posX);
  frc::SmartDashboard::PutNumber("y", posY);
}

void Autonomous::updatePosition(){//calculates position, gets called in a periodic
  // Get relevant values
  double currentAngle = (_getYaw() + angleOffset) * 0.01745329251;  // Convert to radians with * 0.01745329251
  double currentDistance = _getDistance();//total distance
  double distanceDelta = currentDistance - prevDistance;//distance since last 10 milliseconds
  // Determine current position
  posX += distanceDelta * sin(currentAngle);
  posY += distanceDelta * cos(currentAngle);
  // Save values for next iteration
  prevDistance = currentDistance;
}

void Autonomous::setPosition(double x, double y){
  posX = x;
  posY = y;
}

void Autonomous::setAngle(double theta){
  angleOffset = theta - _getYaw();
}

DriveInput Autonomous::autoDrive(double startX, double startY, double endX, double endY, double endHeading){
  //Checks if its a straight line
  if (((int)round(endHeading*10))%1800 == 0){
    if(startX == endX){
      isLinear = true;
    }
  }else if (((int)round((atan((startY-endY)/(startX-endX))*(180/pi))-endHeading)*10)%1800 == 0){
    isLinear = true;
  }else{
    isLinear = false;
  }
  if(isLinear){
    //follow linear line
    double b =  sqrt(pow((startX - endX), 2) + pow((startY - endY), 2));
    double a = sqrt(pow((startX - posX), 2) + pow((startY - posY), 2));
    double c = sqrt(pow((posX - endX), 2) + pow((posY - endY), 2));
    double s = (a+b+c)/2;
    error = sqrt(s*(s-a)*(s-b)*(s-c))*2/b*((endHeading - atan((startY-endY)/(startX-endX))*(180/pi))/abs(endHeading - atan((startY-endY)/(startX-endX))*(180/pi)));
  }else{
    //checks if slope is undefined
    if(((int)round(endHeading*10))%1800 == 0){
      cenX = ((endX*endX) - (startX*startX) - (startY*startY))/((endX - startX));
      cenY = endY;
    }else{
      //calculates slope
      slope = tan((pi*(endHeading-90))/-180);
      //calculates center x and y
      cenX = ( ((endX*endX)*-slope) + (2*endX*(endY-startY)) + (slope*((endY*endY) - (2*endY*startY) + (startX*startX) + (startY*startY))) )/( 2*((slope*(startX-endX)) + endY - startY) );
      cenY = ( (endX*endX) + (2*endX*endY*slope) - (2*endX*startX) - (endY*endY) - (2*endY*startX*slope) + (startX*startX) + (startY) )/( 2*((slope*(startX-endX)) + endY - startY) );
    }
    
    //calculates radius
    radius = sqrt(pow((startX - cenX), 2) + pow((startY - cenY), 2));

    //calculates error based off x,y centre point
    error = sqrt(pow((posX - cenX), 2) + pow((posY - cenY), 2)) - radius;
  }
  //calculates total error or "I"
  intergral = intergral + error;
  //output = kP*Error + kI*Intergral + kD*Derivative
  steering = kP*error + kI*intergral + kD*(error - previousError);
  //Calculates previous error for Derivative
  previousError = error;
  //autoOutput.steering = steering;
  //autoOutput.speed = speed;
  autoOutput.steering = 0;
  autoOutput.speed = 0;
  frc::SmartDashboard::PutNumber("error", error);
  frc::SmartDashboard::PutNumber("cenX", cenX);
  frc::SmartDashboard::PutNumber("cenY", cenY);
  frc::SmartDashboard::PutNumber("radius", radius);
  frc::SmartDashboard::PutBoolean("linear", isLinear);
  return autoOutput;
}