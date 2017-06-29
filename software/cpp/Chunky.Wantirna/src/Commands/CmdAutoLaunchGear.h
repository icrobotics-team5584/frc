#ifndef CMDAUTOLAUNCHGEAR_H
#define CMDAUTOLAUNCHGEAR_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class CmdAutoLaunchGear : public Command {
public:
	CmdAutoLaunchGear();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	int execounter;
	bool finished;
};

#endif  // CMDAUTOLAUNCHGEAR_H
