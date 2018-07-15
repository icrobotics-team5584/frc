
#pragma once

#include "../Robot.h"
#include <Commands/Command.h>

class CmdArmBackMid : public frc::Command {
public:
	CmdArmBackMid();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};
