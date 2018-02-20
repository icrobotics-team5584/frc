#ifndef CmdArmPosClimb_H
#define CmdArmPosClimb_H

#include <Commands/Command.h>
#include "Robot.h"

class CmdArmPosClimb : public Command {
public:
	CmdArmPosClimb();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // CmdArmPosClimb_H
