

#pragma once

#include <Commands/Command.h>
#include "../Robot.h"

class CmdArmDefault : public frc::Command {
public:
	CmdArmDefault();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};

