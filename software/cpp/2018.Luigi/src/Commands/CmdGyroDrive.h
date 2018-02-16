#pragma once

#include <Commands/Command.h>
#include "Robot.h"

class CmdGyroDrive : public frc::Command {
public:
	//Set relative to true if you want turn relative to current angle.
	//Drive distance is always relative and based on the left wheel's movement.
	CmdGyroDrive(double distance, double angle, bool relative = true);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
private:
	double _distance;
	double _angle;
	bool _relative;
	double relativeAngle;
};

