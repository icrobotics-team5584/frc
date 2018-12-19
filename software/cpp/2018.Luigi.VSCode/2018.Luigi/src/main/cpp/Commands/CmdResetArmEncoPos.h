#ifndef CmdResetArmEncoPos_H
#define CmdResetArmEncoPos_H

#include <Commands/Command.h>
#include "Robot.h"

class CmdResetArmEncoPos : public Command {
public:
	CmdResetArmEncoPos();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // CmdResetArmEncoPos_H
