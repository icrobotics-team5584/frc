#ifndef CmdOutput_H
#define CmdOutput_H

#include <Commands/Command.h>
#include "Robot.h"

class CmdOutput : public Command {
public:
	CmdOutput();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // CmdArmDown_H
