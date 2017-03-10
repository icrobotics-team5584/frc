#ifndef CmdAutoMotionProfileToPeg_H
#define CmdAutoMotionProfileToPeg_H

#include "Commands/Subsystem.h"
#include "Custom/MotionProfileExample.h"
#include "../Robot.h"

class CmdAutoMotionProfileToPeg : public Command {
public:
	CmdAutoMotionProfileToPeg();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
private:
	MotionProfileExample _example;
	bool firsttimearound = true;
};

#endif  // CmdAutoMotionProfileToPeg_H
