#ifndef CmdAutoMid_H
#define CmdAutoMid_H

#include "Commands/Command.h"

class CmdAutoMid : public Command {
public:
	CmdAutoMid();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // CmdAutoMid_H
