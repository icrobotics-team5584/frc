#ifndef CmdAutoRight_H
#define CmdAutoRight_H

#include "Commands/Command.h"

class CmdAutoRight : public Command {
public:
	CmdAutoRight();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // CmdAutoRight_H
