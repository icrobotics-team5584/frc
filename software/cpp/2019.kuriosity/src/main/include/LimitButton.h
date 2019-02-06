#pragma once

#include <frc/wpilib.h>
#include <frc/Buttons/Trigger.h>

using namespace frc;

class LimitButton : Trigger {
public:
	LimitButton(DigitalInput* limitSwitch, bool invert);
	bool Get();
	void WhileHeld(Command* command);
    void WhenPressed(Command* command);
private:
	DigitalInput* _limitSwitch;
    bool _invert;
};
