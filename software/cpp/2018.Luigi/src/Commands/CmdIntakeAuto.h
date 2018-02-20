#ifndef CmdIntakeAuto_H
#define CmdIntakeAuto_H

#include <Commands/Command.h>
#include "Robot.h"

class CmdIntakeAuto : public Command {
public:
	CmdIntakeAuto(double timeout = 0, double speed = 0.75);
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
