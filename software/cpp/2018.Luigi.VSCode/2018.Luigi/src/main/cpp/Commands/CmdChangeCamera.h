#ifndef CmdChangeCamera_H
#define CmdChangeCamera_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class CmdChangeCamera : public Command {
public:
	CmdChangeCamera();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // CmdChangeCamera_H
