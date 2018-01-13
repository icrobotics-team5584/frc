#ifndef CmdArmDown_H
#define CmdArmDown_H

#include <Commands/Command.h>
#include "Robot.h"

class CmdArmDown : public Command {
public:
	CmdArmDown();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // CmdArmDown_H
