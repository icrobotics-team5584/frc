#ifndef CMDLAUNCHGEAR_H
#define CMDLAUNCHGEAR_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class CmdLaunchGear : public Command {
public:
	CmdLaunchGear();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // CMDLAUNCHGEAR_H
