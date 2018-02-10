#ifndef CmdOutput_H
#define CmdOutput_H

#include <Commands/Command.h>
#include "Robot.h"

class CmdOutput : public Command {
public:
	CmdOutput(double timeout = 0, double speed = 0.75);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	int _timeout;
	double _speed;
};

#endif  // CmdArmDown_H
