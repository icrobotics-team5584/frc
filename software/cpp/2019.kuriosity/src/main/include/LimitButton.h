#pragma once

#include <frc/wpilib.h>
#include <frc/Buttons/Trigger.h>

using namespace frc;
using namespace std;

class LimitButton : Trigger {
public:
	LimitButton(shared_ptr<DigitalInput> limitSwitch, bool invert);
	bool Get();
	void WhileHeld(Command* command);
    void WhenPressed(Command* command);
private:
	shared_ptr<DigitalInput> _limitSwitch;
    bool _invert;
};
