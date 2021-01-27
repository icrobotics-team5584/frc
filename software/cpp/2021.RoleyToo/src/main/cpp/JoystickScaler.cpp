/*
 * JoystickScaler.cpp
 *
 *  Created on: 26 Jan. 2021
 *      Author: Mitch
 */

#include "JoystickScaler.h"
#include "math.h"

JoystickScaler::JoystickScaler(int deviceID, double scaleLeft, double scaleRight) :
    Joystick(deviceID)
{
    _scaleLeft = scaleLeft;
    _scaleRight = scaleRight;
}

double JoystickScaler::GetScaledX(frc::GenericHID::JoystickHand hand) {

    if (hand == kLeftHand) { _scale = _scaleLeft; }
    if (hand == kRightHand) { _scale = _scaleRight; }

    return pow(Joystick::GetX(hand), _scale);
}

double JoystickScaler::GetScaledY(frc::GenericHID::JoystickHand hand) {

    if (hand == kLeftHand) { _scale = _scaleLeft; }
    if (hand == kRightHand) { _scale = _scaleRight; }

    return pow(Joystick::GetY(hand), _scale);
}