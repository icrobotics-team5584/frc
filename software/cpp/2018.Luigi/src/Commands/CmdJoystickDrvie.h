#ifndef CmdJoystickDrvie_H
#define CmdJoystickDrvie_H

#include <Commands/Command.h>
#include "Commands/Subsystem.h"
#include "../Robot.h"

class CmdJoystickDrvie : public Command {
public:
	CmdJoystickDrvie();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // CmdJoystickDrvie_H
