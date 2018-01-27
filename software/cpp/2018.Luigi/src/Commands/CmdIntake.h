#ifndef CmdIntake_H
#define CmdIntake_H

#include <Commands/Command.h>
#include "Robot.h"

class CmdIntake : public Command {
public:
	CmdIntake();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // CmdArmUp_H
