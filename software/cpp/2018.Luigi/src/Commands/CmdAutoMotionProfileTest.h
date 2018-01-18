#ifndef CmdAutoMotionProfileTest_H
#define CmdAutoMotionProfileTest_H

#include <Commands/Command.h>
#include "Robot.h"
#include "RobotMap.h"
#include "MotionProfileControl.h"
#include "MotionProfiles/MPL-test.h"
#include "MotionProfiles/MPR-test.h"

class CmdAutoMotionProfileTest : public Command {
public:
	CmdAutoMotionProfileTest();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
//	MotionProfileControl MPControl(	RobotMap::subDriveBaseSRXleft,
//									RobotMap::subDriveBaseSRXright,
//									MPLtest, MPRtest);
};

#endif  // CmdAutoMotionProfileTest_H
