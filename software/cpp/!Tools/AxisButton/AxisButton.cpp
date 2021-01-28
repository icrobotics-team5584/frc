/*
 * AxisButton.cpp
 *
 *  Created on: 14 Apr. 2018
 *      Author: Liam
 * 
 *	Updated 20190204_2325 Darcy
 *  Updated 20191204_1954 Mitch
 *  Updated 20210127_1730 Mitch
 * 
 */

#include "AxisButton.h"
#include <iostream>

AxisButton::AxisButton(GenericHID* joystick, int axisNumber, double deadzone) {
	_joystick = joystick;
	_axisNumber = axisNumber;
	_deadzone = deadzone;
}

bool AxisButton::Get(){
	//Return true if the trigger is pressed at all
	if (_joystick->GetRawAxis(_axisNumber) > _deadzone) {
		return true;
	} else {
		return false;
	}
}

void AxisButton::WhileHeld(frc2::Command* command) {
	WhileActiveContinous(command);
}

void AxisButton::WhenPressed(frc2::Command* command) {
	WhenPressed(command);
}

float AxisButton::GetAxis(){
	return _joystick->GetRawAxis(_axisNumber);
	//std::cout << _axisNumber << std::endl;
}

