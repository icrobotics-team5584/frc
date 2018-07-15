
#pragma once

#include "../Robot.h"
#include <Commands/Command.h>

class CmdArmFrontMid : public frc::Command {
public:
	CmdArmFrontMid();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};
