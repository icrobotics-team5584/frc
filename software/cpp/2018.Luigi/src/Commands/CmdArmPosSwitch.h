#ifndef CmdArmPosSwitch_H
#define CmdArmPosSwitch_H

#include <iostream>
#include <Commands/Command.h>
#include "Robot.h"

class CmdArmPosSwitch : public Command {
public:
	CmdArmPosSwitch();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // CmdArmPosSwitch_H
