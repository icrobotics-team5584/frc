#ifndef CmdAutoLeft_H
#define CmdAutoLeft_H

#include "Commands/Command.h"
#include "Robot.h"

class CmdAutoLeft : public Command {
public:
	CmdAutoLeft();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // CmdAutoLeft_H
