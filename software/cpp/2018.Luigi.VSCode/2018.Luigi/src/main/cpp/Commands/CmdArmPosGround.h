#ifndef CmdArmPosGround_H
#define CmdArmPosGround_H

#include <Commands/Command.h>
#include "Robot.h"

class CmdArmPosGround : public Command {
public:
	CmdArmPosGround();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // CmdArmPosGround_H
