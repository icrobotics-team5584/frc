#ifndef CmdRampDefault_H
#define CmdRampDefault_H

#include <Commands/Command.h>
#include "Robot.h"
#include <SmartDashboard/SmartDashboard.h>

class CmdRampDefault : public Command {
public:

	std::shared_ptr<Joystick> sticky_3;
	int _POV = 0;

	CmdRampDefault();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // CmdRampDefault_H
