#ifndef CmdIntake_H
#define CmdIntake_H

#include <Commands/Command.h>
#include "Robot.h"

class CmdIntake : public Command {
public:
	CmdIntake(int timeout = 0);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	int _timeout;
};

#endif  // CmdArmUp_H
