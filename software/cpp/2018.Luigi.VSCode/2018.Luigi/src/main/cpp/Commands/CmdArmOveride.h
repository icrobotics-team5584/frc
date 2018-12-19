#ifndef CmdArmOveride_H
#define CmdArmOveride_H

#include <Commands/Command.h>
#include "Robot.h"

class CmdArmOveride : public Command {
public:
	CmdArmOveride();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // CmdArmOveride_H
