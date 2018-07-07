#pragma once


#include <WPILib.h>
#include <String>
#include "GameData.h"
#include "../Commands/AllAutoRoutines.h"


class AutonomousSelector {
public:
	AutonomousSelector();
	std::shared_ptr<Command> DetermineRoutine(GameData gameData);


private:
	std::shared_ptr<GameData> _gameData;

	enum StartingPosition {startLeft, startMiddle, startRight};

	std::shared_ptr<SendableChooser<StartingPosition>> positionSelector;
	StartingPosition spLeft = startLeft;
	StartingPosition spMid = startMiddle;
	StartingPosition spRight = startRight;
};
