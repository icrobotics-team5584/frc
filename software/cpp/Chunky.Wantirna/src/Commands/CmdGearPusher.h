#ifndef CmdActuator1Out_H
#define CmdActuator1Out_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class CmdGearPusher : public Command {
public:
	CmdGearPusher();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // CmdActuator1Out_H
