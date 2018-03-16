#ifndef CmdArmPosScaleLow_H
#define CmdArmPosScaleLow_H

#include <Commands/Command.h>
#include "Robot.h"

class CmdArmPosScaleLow : public Command {
public:
	CmdArmPosScaleLow();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // CmdArmPosScaleLow_H
