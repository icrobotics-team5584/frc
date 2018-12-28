#include "purePursuit/include/PosEncoderGyro.h"
#include "Robot.h"
#include <iostream>

PosEncoderGyro::PosEncoderGyro() {
    prevPoint.velocity = 0;
    prevPoint.x = 0;
    prevPoint.y = 0;
}

bool PosEncoderGyro::ping() {
    return true;
}

Point PosEncoderGyro::get() {
    Point currentPoint;

    // Get relevant values
    double currentAngle = Robot::subDriveBase->getAngle();
    double currentDistance = Robot::subDriveBase->getDistance();
    double distanceDelta = currentDistance - prevDistance;

    // Determine current position
    currentPoint.x = distanceDelta * cos(currentAngle);
    currentPoint.y = distanceDelta * sin(currentAngle);
    currentPoint.velocity = distanceDelta / 0.02; // Presumed to run every 20ms

    // Save values for next iteration
    prevPoint = currentPoint;
    prevDistance = currentDistance;

    return currentPoint;
}