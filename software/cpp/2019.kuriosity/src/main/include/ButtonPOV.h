/*
 *  ButtonPOV.h
 *
 *  Created on: 20190102
 *  Author: Darcy Meago
 */

#pragma once
#include <frc/WPILib.h>
#include <frc/buttons/Trigger.h>
#include <cstdlib>

using namespace frc;

class ButtonPOV : Trigger {
public:
	ButtonPOV(GenericHID* joystick, int position);
	bool Get();
	void WhileHeld(Command* command);
private:
	GenericHID* _joystick;
	int _position = 0;

    int _extraZone = 10;
    int _upper = 0;
    int _lower = 0;
};


