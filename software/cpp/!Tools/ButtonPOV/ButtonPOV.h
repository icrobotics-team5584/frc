/*
 *  ButtonPOV.h
 *
 *  Created on: 20190102
 *  Author: Darcy Meago
 */

#pragma once
#include "frc/Joystick.h"
#include <frc2/command/button/Trigger.h>
#include <cstdlib>

using namespace frc;

class ButtonPOV : frc2::Trigger {
public:
	ButtonPOV(GenericHID* joystick, int position);
	bool Get();
	void WhenPressed(frc2::Command& command);
    void WhileHeld(frc2::Command& command);
private:
	GenericHID* _joystick;
	int _position = 0;
    int _extraZone = 10;
    int _upper = 0;
    int _lower = 0;
};


