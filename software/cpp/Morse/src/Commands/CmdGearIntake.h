#ifndef CmdGearIntake_H
#define CmdGearIntake_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class CmdGearIntake : public Command {
public:
	CmdGearIntake();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // CmdGearIntake_H
