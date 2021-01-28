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
#include <frc2/command/button/Trigger.h>

using namespace frc;

class AxisButton : 
frc2::Trigger {
public:
	AxisButton(GenericHID* joystick, int axisNumber, double deadzone = 0);
	bool Get();
	float GetAxis();
	void WhenPressed(frc2::Command& command);
	void WhileHeld(frc2::Command& command);
private:
	GenericHID* _joystick;
	int _axisNumber;
	double _deadzone;
};
