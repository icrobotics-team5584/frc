#include "purePursuit/include/PosEncoderGyro.h"
#include "Robot.h"
#include <iostream>
#include <cmath>

PosEncoderGyro::PosEncoderGyro() {
    currentPoint.velocity = 0;
    currentPoint.x = 0;
    currentPoint.y = 0;
    timer.Start();
}

Point PosEncoderGyro::get() {
    //Check time period
    SmartDashboard::PutNumber("time interval", timer.Get());
    timer.Reset();

    // Get relevant values
    double currentAngle = Robot::subDriveBase->getAngle() * 0.01745329251; // Convert to radians
    double currentDistance = Robot::subDriveBase->getDistance();
    double distanceDelta = currentDistance - prevDistance;
    SmartDashboard::PutNumber("distanceDelta", distanceDelta);

    // Determine current position
    currentPoint.x += distanceDelta * cos(currentAngle);
    currentPoint.y += distanceDelta * sin(currentAngle);
    currentPoint.velocity = distanceDelta / 0.02; // Presumed to run every 20ms

    // Save values for next iteration
    prevDistance = currentDistance;

    return currentPoint;
}