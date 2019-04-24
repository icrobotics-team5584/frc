
#pragma once
#include <iostream>
#include <frc/wpilib.h>
#include <frc/Buttons/Trigger.h>
using namespace frc;

class ToggleButton : Trigger {
 public:
  ToggleButton(GenericHID* joystick, int axisNumber, bool isAxis = false);
	bool Get();
	float GetAxis();
	void WhenPressed();
	void WhileHeld(Command* command);
  void SetCommand(Command* cmd1, Command* cmd2);
private:
	GenericHID* _joystick;
	int _axisNumber;
  bool _isAxis;
  Command* _cmd1;
  Command* _cmd2;
  bool prevState = false;
};
