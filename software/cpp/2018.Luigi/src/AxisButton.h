/*
 * AxisButton.h
 *
 *  Created on: 14 Apr. 2018
 *      Author: Liam
 */
#include <wpilib.h>
#include <Buttons/Trigger.h>

#ifndef SRC_AXISBUTTON_H_
#define SRC_AXISBUTTON_H_

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

#endif /* SRC_AXISBUTTON_H_ */
