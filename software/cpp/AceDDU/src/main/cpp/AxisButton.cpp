/*
 * AxisButton.cpp
 *
 *  Created on: 14 Apr. 2018
 *      Author: Liam
 * 
 *	Updated 20190204_2325 Darcy
 * 
 */

#include <AxisButton.h>
#include <iostream>

AxisButton::AxisButton(GenericHID* joystick, int axisNumber) {
	_joystick = joystick;
	_axisNumber = axisNumber;
}

bool AxisButton::Get(){
	//Return true if the trigger is pressed at all
	if (_joystick->GetRawAxis(_axisNumber) > 0) {
		return true;
	} else {
		return false;
	}
}

void AxisButton::WhileHeld(Command* command) {
	WhileActive(command);
}

void AxisButton::WhenPressed(Command* command) {
	WhenActive(command);
}

float AxisButton::GetAxis(){
	return _joystick->GetRawAxis(_axisNumber);
	std::cout << _axisNumber << std::endl;
}

