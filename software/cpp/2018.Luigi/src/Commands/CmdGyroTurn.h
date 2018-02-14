#pragma once

#include <Commands/Command.h>
#include "Robot.h"

class CmdGyroTurn : public frc::Command {
public:
	CmdGyroTurn(double angle, bool relative); //set relative to true if you want turn relative to current angle
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
private:
	double _angle;
	bool _relative;
	double relativeAngle;
};

