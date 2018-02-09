#ifndef CmdRampDrop_H
#define CmdRampDrop_H

#include <Commands/Command.h>
#include "Robot.h"

class CmdRampDrop : public Command {
public:
	CmdRampDrop();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // CmdRampDrop_H
