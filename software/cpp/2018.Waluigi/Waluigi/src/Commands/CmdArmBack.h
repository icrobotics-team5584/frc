
#pragma once

#include "../Robot.h"
#include <Commands/Command.h>

class CmdArmBack : public frc::Command {
public:
	CmdArmBack();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};

