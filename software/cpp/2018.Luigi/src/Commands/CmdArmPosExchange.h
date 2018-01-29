#ifndef CmdArmPosExchange_H
#define CmdArmPosExchange_H

#include <Commands/Command.h>
#include "Robot.h"

class CmdArmPosExchange : public Command {
public:
	CmdArmPosExchange();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // CmdArmPosExchange_H
