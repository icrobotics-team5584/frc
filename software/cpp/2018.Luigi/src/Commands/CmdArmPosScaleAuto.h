#ifndef CmdArmPosScaleAuto_H
#define CmdArmPosScaleAuto_H

#include <Commands/Command.h>
#include "Robot.h"

class CmdArmPosScaleAuto : public Command {
public:
	CmdArmPosScaleAuto();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // CmdArmPosScaleAuto_H
