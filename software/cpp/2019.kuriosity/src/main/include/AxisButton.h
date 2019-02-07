/*
 * AxisButton.h
 *
 *  Created on: 14 Apr. 2018
 *      Author: Liam
 * 	
 * 	Updated 20190204_2325 Darcy 
 * 
 */
#pragma once

#include <frc/wpilib.h>
#include <frc/Buttons/Trigger.h>

using namespace frc;

class AxisButton : Trigger {
public:
	AxisButton(GenericHID* joystick, int axisNumber);
	bool Get();
	float GetAxis();
	void WhileHeld(Command* command);
private:
	GenericHID* _joystick;
	int _axisNumber;
};
