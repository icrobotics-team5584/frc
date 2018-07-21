
#pragma once

#include "../Robot.h"
#include <Commands/Command.h>

class CmdArmUp : public frc::Command {
public:
	CmdArmUp();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};
