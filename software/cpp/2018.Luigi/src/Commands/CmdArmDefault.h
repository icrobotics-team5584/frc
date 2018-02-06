#ifndef CmdArmDefault_H
#define CmdArmDefault_H

#include <Commands/Command.h>
#include "Robot.h"

class CmdArmDefault : public Command {
public:
	CmdArmDefault();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // CmdArmDefault_H
