#ifndef CmdActuator2Out_H
#define CmdActuator2Out_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class CmdGearDoorsOpen : public Command {
public:
	CmdGearDoorsOpen();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // CmdActuator2Out_H
