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
    /*
    code 
    here
    */
    //calculates slope
    slope = endHeading;//to do
    //****BRUH****
    cenX = ( ((startX*startX)*-slope) + (2*startX*(startY-endY)) + (slope*((startY*startY) - (2*startY*endY) + (endX*endX) + (endY*endY))) )/( 2*((slope*(endX-startX)) + startY - endY) );
    cenY = ( (startX*startX) + (2*startX*startY*slope) - (2*startX*endX) - (startY*startY) - (2*startY*endX*slope) + (endX*endX) + (endY) )/( 2*((slope*(endX-startX)) + startY - endY) );
    //calculates radius
    radius = 1;//todo
    //calculates error based off x,y centre point
    error = sqrt(pow((posX - cenX), 2) + pow((posY - cenY), 2)) - radius;
    //calculates total error or "I"
    intergral = intergral + error;
    //output = kP*Error + kI*Intergral + kD*Derivative
    steering = kP*error + kI*intergral + kD*(error - previousError);
    //Calculates previous error for Derivative
    previousError = error;
    autoOutput.steering = steering;
    autoOutput.speed = speed;
    frc::SmartDashboard::PutNumber("error", error);
    return autoOutput;
}