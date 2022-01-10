/*
 * JoystickScaler.cpp
 *
 *  Created on: 26 Jan. 2021
 *      Author: Mitch
 */

#include "Utilities/JoystickScaler.h"
#include "math.h"

JoystickScaler::JoystickScaler(int deviceID, double scaleLeft, double scaleRight) :
    XboxController(deviceID)
{
    _scaleLeft = scaleLeft;
    _scaleRight = scaleRight;
}

double JoystickScaler::GetScaledX(Hand hand) {

    double controllerValue = 0;
    if (hand == left) { 
        _scale = _scaleLeft;
        controllerValue = XboxController::GetLeftX(); 
    }
    if (hand == right) { 
        _scale = _scaleRight; 
        controllerValue = XboxController::GetRightX();
    }
    
    //std::cout << "xS " << pow(Joystick::GetX(hand), _scale) << "xR " << Joystick::GetX(hand);

    if (controllerValue < 0) {
        return pow(abs(controllerValue), _scale);
    }
    else {
        return -1 * pow(abs(controllerValue), _scale);
    }
}

double JoystickScaler::GetScaledY(Hand hand) {

    double controllerValue = 0;
    if (hand == left) { 
        _scale = _scaleLeft;
        controllerValue = XboxController::GetLeftY(); 
    }
    if (hand == right) { 
        _scale = _scaleRight; 
        controllerValue = XboxController::GetRightY();
    }

    //std::cout << "yS " << pow(Joystick::GetY(hand), _scale) << "yR " << Joystick::GetY(hand) << "\n";

    if (controllerValue < 0) {
        return -1 * pow(abs(controllerValue), _scale);
    }
    else {
        return pow(abs(controllerValue), _scale);
    }
}

void JoystickScaler::SetLeftScale(double scale) {
    _scaleLeft = scale;
}

void JoystickScaler::SetRightScale(double scale) {
    _scaleRight = scale;
}