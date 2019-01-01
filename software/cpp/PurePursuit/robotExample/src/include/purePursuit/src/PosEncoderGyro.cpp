#include "purePursuit/include/PosEncoderGyro.h"
#include <cmath>
#include <iostream>
#include "Robot.h"

PosEncoderGyro::PosEncoderGyro() {
    currentPosition.first = 0;
    currentPosition.second = 0;
    timer.Start();
}

void PosEncoderGyro::reset() {
    currentPosition.first = 0;
    currentPosition.second = 0;
    Robot::subDriveBase->zeroEncoders();
}

/*
 * Determines the robot's current position as represented by an x and y value
 */
pair<double, double> PosEncoderGyro::get() {
    // Check time period
    SmartDashboard::PutNumber("time interval", timer.Get());
    timer.Reset();

    // Get relevant values
    double currentAngle =
        Robot::subDriveBase->getAngle() * 0.01745329251;  // Convert to radians
    double currentDistance = Robot::subDriveBase->getDistance();
    double distanceDelta = currentDistance - prevDistance;
    SmartDashboard::PutNumber("distanceDelta", distanceDelta);

    // Determine current position
    currentPosition.first += distanceDelta * cos(currentAngle);
    currentPosition.second += distanceDelta * sin(currentAngle);

    // Save values for next iteration
    prevDistance = currentDistance;

    return currentPosition;
}

void PosEncoderGyro::set(double x, double y) {
    currentPosition.first = x;
    currentPosition.second = y;
}