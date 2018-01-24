#pragma once

#include <string.h>
#include <SmartDashboard/SmartDashboard.h>
#include "GameData.h"

/*
 * At the start of the autonomous period, the AutonomousSelector class will
 * pull in game data from the FMS (using the GameData class), the robot's
 * starting position and a selection of which task to perform (from the Dash-board).
 * The DetermineMotionProfile function will select a MP to run based on those
 * inputs.
 */

class AutonomousSelector {
public:
	enum StartingPos {Left, Mid, Right};

	AutonomousSelector();
	std::string DetermineMotionProfile(StartingPos);

private:
	enum Task {Nothing = 0, Scale = 1, Switch = 2, Both = 3};
	Task autonomousTask;
	GameData gameData;
	std::string MPName;
};
