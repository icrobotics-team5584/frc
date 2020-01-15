/*
 * AxisButton.h
 *
 *  Created on: 14 Apr. 2018
 *      Author: Liam
 * 	
 * 	Updated 20190204_2325 Darcy 
 *  Updated 20191204_1954 Mitch
 * 
 */
#pragma once

#include <frc/Joystick.h>
#include <frc/Buttons/Trigger.h>

using namespace frc;

class AxisButton : Trigger {
public:
	AxisButton(GenericHID* joystick, int axisNumber,  int deadzone = 0);
	bool Get();
	float GetAxis();
	void WhenPressed(Command* command);
	void WhileHeld(Command* command);
private:
	GenericHID* _joystick;
	int _axisNumber;
	int _deadzone;
};
