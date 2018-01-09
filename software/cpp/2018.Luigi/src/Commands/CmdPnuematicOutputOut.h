#ifndef CmdPnuematicOutputOut_H
#define CmdPnuematicOutputOut_H

#include <Commands/Command.h>

class CmdPnuematicOutputOut : public frc::Command {
public:
	CmdPnuematicOutputOut();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // CmdPnuematicOutputOut_H
