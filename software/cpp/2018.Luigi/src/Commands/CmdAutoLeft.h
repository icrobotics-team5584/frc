#ifndef CmdAutoLeft_H
#define CmdAutoLeft_H

#include <string.h>
#include <Commands/Command.h>
#include "Robot.h"
#include "RobotMap.h"
#include "MotionProfileControl.h"
#include "MotionProfileData.h"
#include "GameData.h"
#include "AutonomousSelector.h"

class CmdAutoLeft : public Command {
public:
	CmdAutoLeft();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	std::shared_ptr<MotionProfileData> MPData;
	MotionProfileControl MPController;
	GameData gameData;
	AutonomousSelector autoSelector;
};
#endif  // CmdAutoLeft_H
