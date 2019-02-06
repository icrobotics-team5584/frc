#pragma once

#include <frc/wpilib.h>
#include <frc/Buttons/Trigger.h>

using namespace frc;

class LimitButton : Trigger {
public:
	LimitButton(DigitalInput* _limitSwitch, bool _invert);
	bool Get();
	void WhileHeld(Command* command);
    void WhenPressed(Command* command);
private:
	DigitalInput* _limitSwitch;
    bool _invert;
};
