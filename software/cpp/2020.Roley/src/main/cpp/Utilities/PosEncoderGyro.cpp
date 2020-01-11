#include "Utilities/PosEncoderGyro.h"
#include <cmath>
#include "Robot.h"

PosEncoderGyro::PosEncoderGyro() {
    currentPosition.x = 0;
    currentPosition.y = 0;
}

/*
 * Determines the robot's current position as represented by an x and y value
 */
double PosEncoderGyro::getPositionx() {
    return currentPosition.x;
}

double PosEncoderGyro::getAngle() {
    return Robot::subDriveBase->getYaw() * 0.01745329251;
}

void PosEncoderGyro::setPosition(double x, double y) {
    currentPosition.x = x;
    currentPosition.y = y;
    // currentPosition.x = 1.2;
    // currentPosition.y = 1;
}

void PosEncoderGyro::reset() {
    currentPosition.x = 0;
    currentPosition.y = 0;
    Robot::subDriveBase->zeroEncoders();
}

void PosEncoderGyro::updatePosition(){
    // Get relevant values
    double currentAngle = Robot::subDriveBase->getYaw() * 0.01745329251;  // Convert to radians with * 0.01745329251
    double currentDistance = Robot::subDriveBase->getDistanceTravelled();
    double distanceDelta = currentDistance - prevDistance;
    // Determine current position
    currentPosition.x += distanceDelta * sin(currentAngle);
    currentPosition.y += distanceDelta * cos(currentAngle);
    frc::SmartDashboard::PutNumber("dollyx", currentPosition.x);
    frc::SmartDashboard::PutNumber("dollyy", currentPosition.y);
    // Save values for next iteration
    prevDistance = currentDistance;
}