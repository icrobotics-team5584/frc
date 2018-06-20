

#pragma once

//#include "Commands/Subsystem.h"
#include "../Robot.h"
#include <Commands/Command.h>

class CmdArmJoy : public frc::Command {
public:
	CmdArmJoy();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};

