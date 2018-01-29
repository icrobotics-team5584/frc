#ifndef CmdAutonomous_H
#define CmdAutonomous_H

#include "Commands/Command.h"
#include "Robot.h"
#include "AutonomousSelector.h"
#include "MotionProfileData.h"
#include "MotionProfileControl.h"

class CmdAutonomous : public Command {
public:
	CmdAutonomous();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	AutonomousSelector autoSelector;
	MotionProfileControl MPController;
};

#endif  // CmdAutonomous_H
