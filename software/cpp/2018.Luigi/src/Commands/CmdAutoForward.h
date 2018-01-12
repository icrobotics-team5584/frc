#ifndef CmdAutoForward_H
#define CmdAutoForward_H

#include <Commands/Command.h>
#include "Robot.h"

class CmdAutoForward : public Command {
public:
	CmdAutoForward();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // CmdAutoForward_H
