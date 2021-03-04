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
  
  frc::SmartDashboard::PutNumber("distance", currentDistance);
  double distanceDelta = currentDistance - prevDistance;//distance since last 10 milliseconds
  // Determine current position
  dollyPosX += distanceDelta * sin(currentAngle);
  dollyPosY += distanceDelta * cos(currentAngle);
  frontPosX = dollyPosX + (metersToFront * sin(currentAngle));
  frontPosY = dollyPosY + (metersToFront * cos(currentAngle));
  backPosX = dollyPosX - (metersToBack * sin(currentAngle));
  backPosY = dollyPosY - (metersToBack * cos(currentAngle));
  // Save values for next iteration
  prevDistance = currentDistance;
}

void Autonomous::setPosition(double x, double y){
  dollyPosX = x;
  dollyPosY = y;
}

void Autonomous::setAngle(double theta){
  angleOffset = theta - _getYaw();
}

DriveInput Autonomous::autoDrive(double startX, double startY, double endX, double endY, double endHeading, double cenX, double cenY, PIDk PIDk, double speed){
  if(speed >= 0){
    posX = frontPosX;
    posY = frontPosY;
  }else{
    posX = backPosX;
    posY = backPosY;
  }
  //Checks if its a straight line
  if (((int)round((atan2(endX-startX,endY-startY)*(180/pi))-endHeading)*10)%1800 == 0){
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
    
    error = sqrt(s*(s-a)*(s-b)*(s-c))*2/b;
  }else{
    //checks if slope is undefined
    /*if(((int)round(endHeading*10))%1800 == 0){
      cenX = ((endX*endX) - (startX*startX) - (startY*startY))/((endX - startX));
      cenY = endY;
    }else{
      //calculates slope
      slope = tan((pi*(endHeading-90))/-180);
      //calculates center x and y
      cenX = ( ((endX*endX)*-slope) + (2*endX*(endY-startY)) + (slope*((endY*endY) - (2*endY*startY) + (startX*startX) + (startY*startY))) )/( 2*((slope*(startX-endX)) + endY - startY) );
      cenY = ( (endX*endX) + (2*endX*endY*slope) - (2*endX*startX) - (endY*endY) - (2*endY*startX*slope) + (startX*startX) + (startY) )/( 2*((slope*(startX-endX)) + endY - startY) );
    }*/
    
    //calculates radius
    radius = sqrt(pow((startX - cenX), 2) + pow((startY - cenY), 2));
    //Checks the direction  
    //frc::SmartDashboard::PutNumber("Heading of line to end", (atan((cenY-endY)/(cenX-endX))*(-180/pi)));
    //frc::SmartDashboard::PutNumber("Heading of line to start", (atan((cenY-startY)/(cenX-startX))*(-180/pi)));
    //frc::SmartDashboard::PutNumber("difference", (atan((endY-cenY)/(endX-cenX))*(180/pi))-(atan((startY-cenY)/(startX-cenX))*(180/pi)));
    //calculates error based off x,y centre point
    frc::SmartDashboard::PutNumber("slope of end", (cenY-endY)/(cenX-endX));
    frc::SmartDashboard::PutNumber("slope of start", (cenY-startY)/(cenX-startX));
    error = sqrt(pow((posX - cenX), 2) + pow((posY - cenY), 2)) - radius;
  }
  //calculates total error or "I"
  intergral = intergral + error;
  //output = kP*Error + kI*Intergral + kD*Derivative
  steering = PIDk.p*error + PIDk.i*intergral + PIDk.d*(error - previousError);
  //Calculates previous error for Derivative
  previousError = error;
  autoOutput.steering = steering;
  autoOutput.speed = speed;
  //autoOutput.steering = 0;
  //autoOutput.speed = 0;
  
  //std::cout<<"Running"<<std::endl;
  frc::SmartDashboard::PutNumber("error", error);
  frc::SmartDashboard::PutNumber("cenX", cenX);
  frc::SmartDashboard::PutNumber("cenY", cenY);
  frc::SmartDashboard::PutNumber("radius", radius);
  frc::SmartDashboard::PutBoolean("linear", isLinear);
  frc::SmartDashboard::PutNumber("midx", dollyPosX);
  frc::SmartDashboard::PutNumber("midy", dollyPosY);
  frc::SmartDashboard::PutNumber("front y", frontPosY);
  frc::SmartDashboard::PutNumber("frontx", frontPosX);
  frc::SmartDashboard::PutNumber("auto angle", _getYaw() + angleOffset);
  return autoOutput;
}

bool Autonomous::end(double endx, double endy, double endHeading){
  frc::SmartDashboard::PutNumber("angle thing", abs(endHeading-(atan2(posY-endy, posX-endx)*(-180/pi)+90)));
  if(abs(endHeading-(atan2(posY-endy, posX-endx)*(-180/pi)+90)) < 90){
    return true;
  }else{
    return false;
  }
}

DriveInput Autonomous::turnTo(double angle, PIDk PIDk){
  error = (_getYaw() + angleOffset) - angle;
  intergral = intergral + error;
  steering = PIDk.p*error + PIDk.i*intergral + PIDk.d*(error - previousError);
  frc::SmartDashboard::PutNumber("Steering", steering);
  frc::SmartDashboard::PutNumber("angle", _getYaw() + angleOffset);
  frc::SmartDashboard::PutNumber("error", error);
  previousError = error;
  autoOutput.steering = steering;
  autoOutput.speed = 0;
  return autoOutput;
}

bool Autonomous::turnToEnd(double angle){
  if(/*round((_getYaw() + angleOffset) - angle) == 0 &&*/ abs(steering) < 0.1){
    return true;
  }else{
    return false;
  }
}