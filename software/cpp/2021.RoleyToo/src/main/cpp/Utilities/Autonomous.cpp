// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Utilities/Autonomous.h"
#include "RobotContainer.h"
Autonomous::Autonomous(std::function<double()> getYaw, std::function<double()> getDistance){
    _getYaw = getYaw;
    _getDistance = getDistance;
    prevDistance = _getDistance();
    notifier.StartPeriodic(fasterPeriod);
}

void Autonomous::Periodic(){
    updatePosition();
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

void Autonomous::autoDrive(std::string curve){
    
}