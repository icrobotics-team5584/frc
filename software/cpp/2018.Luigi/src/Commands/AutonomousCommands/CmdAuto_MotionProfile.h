#ifndef CmdAuto_MotionProfile_H
#define CmdAuto_MotionProfile_H

#include <string>
#include "Commands/Command.h"
#include "Robot.h"
#include "Autonomous/AutonomousSelector.h"
#include "Autonomous/MotionProfileData.h"
#include "Autonomous/MotionProfileControl.h"

class CmdAuto_MotionProfile : public Command {
public:
	CmdAuto_MotionProfile(std::string profile);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	MotionProfileControl MPController;
};

#endif  // CmdAuto_MotionProfile_H
