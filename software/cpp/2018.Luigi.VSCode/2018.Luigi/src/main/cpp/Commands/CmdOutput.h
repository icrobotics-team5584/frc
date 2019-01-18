#ifndef CmdOutput_H
#define CmdOutput_H

#include <Commands/Command.h>
#include "Robot.h"

class CmdOutput : public Command {
public:
	CmdOutput(double timeout = 0, double speed = 0.5, bool variableSpeed = false);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	int _timeout;
	double _speed;
	bool _variableSpeed;
};

#endif  // CmdArmDown_H
