
#pragma once

#include "../Robot.h"
#include <Commands/Command.h>

class CmdArmFront : public frc::Command {
public:
	CmdArmFront();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};

