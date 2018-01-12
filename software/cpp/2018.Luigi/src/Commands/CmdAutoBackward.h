#ifndef CmdAutoBackward_H
#define CmdAutoBackward_H

#include <Commands/Command.h>

#include "Robot.h"

class CmdAutoBackward : public Command {
public:
	CmdAutoBackward();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // CmdAutoBackward_H
