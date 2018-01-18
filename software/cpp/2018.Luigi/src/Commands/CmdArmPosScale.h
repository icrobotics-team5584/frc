#ifndef CmdArmPosScale_H
#define CmdArmPosScale_H

#include <Commands/Command.h>
#include "Robot.h"

class CmdArmPosScale : public Command {
public:
	CmdArmPosScale();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // CmdArmPosScale_H
