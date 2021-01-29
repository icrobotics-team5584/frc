/*
 * JoystickScaler.cpp
 *
 *  Created on: 26 Jan. 2021
 *      Author: Mitch
 */

#include "Utilities/JoystickScaler.h"
#include "math.h"

JoystickScaler::JoystickScaler(int deviceID, double scaleLeft, double scaleRight) :
    Joystick(deviceID)
{
    _scaleLeft = scaleLeft;
    _scaleRight = scaleRight;
}

double JoystickScaler::GetScaledX(frc::GenericHID::JoystickHand hand) {

    if (hand == frc::GenericHID::JoystickHand::kLeftHand) { _scale = _scaleLeft; }
    if (hand == frc::GenericHID::JoystickHand::kRightHand) { _scale = _scaleRight; }
    
    std::cout << "xS " << pow(Joystick::GetX(hand), _scale) << "xR " << Joystick::GetX(hand);
    
    if (Joystick::GetX(hand) < 0) {
        return -1 * pow(abs(Joystick::GetX(hand)), _scale);
    }
    else {
        return pow(abs(Joystick::GetX(hand)), _scale);
    }
}

double JoystickScaler::GetScaledY(frc::GenericHID::JoystickHand hand) {

    if (hand == frc::GenericHID::JoystickHand::kLeftHand) { _scale = _scaleLeft; }
    if (hand == frc::GenericHID::JoystickHand::kRightHand) { _scale = _scaleRight; }

    std::cout << "yS " << pow(Joystick::GetY(hand), _scale) << "yR " << Joystick::GetY(hand) << "\n";

    if (Joystick::GetY(hand) < 0) {
        return -1 * pow(abs(Joystick::GetY(hand)), _scale);
    }
    else {
        return pow(abs(Joystick::GetY(hand)), _scale);
    }
}

void JoystickScaler::SetLeftScale(double scale) {
    _scaleLeft = scale;
}

void JoystickScaler::SetRightScale(double scale) {
    _scaleRight = scale;
}