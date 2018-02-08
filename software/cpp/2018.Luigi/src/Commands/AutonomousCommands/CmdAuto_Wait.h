#ifndef CmdAuto_Wait_H
#define CmdAuto_Wait_H

#include "Commands/Command.h"

class CmdAuto_Wait : public Command {
public:
	CmdAuto_Wait(double timeout);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	double _timeout;
};

#endif  // CmdAuto_Wait_H
