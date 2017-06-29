#ifndef CMDAUTORESETGEAR_H
#define CMDAUTORESETGEAR_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class CmdAutoResetGear : public Command {
public:
	CmdAutoResetGear();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	int execounter;
	bool finished;
};

#endif  // CMDAUTORESETGEAR_H
