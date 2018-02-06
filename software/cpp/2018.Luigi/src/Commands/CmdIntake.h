#ifndef CmdIntake_H
#define CmdIntake_H

#include <Commands/Command.h>
#include "Robot.h"

class CmdIntake : public Command {
public:
	CmdIntake(double timeout = 0, double speed = 0.75);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	int _timeout;
	double _speed;
};

#endif  // CmdArmUp_H
