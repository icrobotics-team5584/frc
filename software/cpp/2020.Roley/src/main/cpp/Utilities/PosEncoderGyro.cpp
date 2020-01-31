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
double PosEncoderGyro::getPositionX() {//returns position that is calculated in updateAbsolutePosition()
    return currentPosition.x;
}

double PosEncoderGyro::getTempPositionX(){
    return tempPosition.x;
}

double PosEncoderGyro::getPositionY() {
    return currentPosition.y;
}

double PosEncoderGyro::getTempPositionY() {
    return tempPosition.y;
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

void PosEncoderGyro::setTempPosition(double x, double y) {
    tempPosition.x = x;
    tempPosition.y = y;
}

void PosEncoderGyro::setInitialAngle(double angle){
    double _angle = angle;
    initialAngleOffset = Robot::subDriveBase->getActualYaw() + _angle;
}

void PosEncoderGyro::setTempAngle(double tAngle){
    Robot::subDriveBase->setTargetYaw(tAngle);
}


void PosEncoderGyro::reset() {
    currentPosition.x = 0;
    currentPosition.y = 0;
    Robot::subDriveBase->zeroEncoders();
}

void PosEncoderGyro::updateAbsolutePosition(){//calculates position, gets called in a periodic somewhere
    // Get relevant values
    double currentAngle = (Robot::subDriveBase->getActualYaw() + initialAngleOffset) * 0.01745329251;  // Convert to radians with * 0.01745329251
    double currentDistance = Robot::subDriveBase->getDistanceTravelled();//total distance
    double distanceDelta = currentDistance - prevDistance;//distance since last 20 millisecond
    // Determine current position
    currentPosition.x += distanceDelta * sin(currentAngle);
    currentPosition.y += distanceDelta * cos(currentAngle);
    // Save values for next iteration
    prevDistance = currentDistance;
}

void PosEncoderGyro::updateRelativePosition(){
    // Get relevant values
    double currentTAngle = (Robot::subDriveBase->getYaw()) * 0.01745329251;  // Convert to radians with * 0.01745329251
    double currentTDistance = Robot::subDriveBase->getDistanceTravelled();//total distance
    double tDistanceDelta = currentTDistance - prevTDistance;//distance since last 20 millisecond
    // Determine current position
    tempPosition.x += tDistanceDelta * sin(currentTAngle);
    tempPosition.y += tDistanceDelta * cos(currentTAngle);
    // Save values for next iteration
    prevTDistance = currentTDistance;
}