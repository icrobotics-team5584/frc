#pragma once

#include <string.h>
#include <Commands/Command.h>
#include <SmartDashboard/SmartDashboard.h>
#include "GameData.h"

//Include possible autonomous tasks
#include "AutoCommandsIncludes.h"	//I don't know if this is bad practice, it seems nice though.

/*
 * At the start of the autonomous period, the AutonomousSelector class will
 * pull in game data from the FMS (using the GameData class), the robot's
 * starting position and a selection of which task to perform (from the Dash-board).
 * The SelectAndRun function will select a command to run based on those inputs
 * and run it.
 */

class AutonomousSelector {
public:
	enum StartingPosition {Left, Middle, Right};
	enum AutonomousTask {Switch, Scale, Both, Nothing};

	AutonomousSelector();
	std::string DetermineRoutine(StartingPosition pos, AutonomousTask task, GameData data);
	std::shared_ptr<frc::Command> DetermineCommand(std::string Routine);
	void SelectAndRun(StartingPosition pos, AutonomousTask task, GameData data);
	void ReadMotionProfile(std::string MP);
	void SendOptionsToDashboard();
	AutonomousTask GetAutonomousTask();
	StartingPosition GetStartingPosition();

	//Declare subclasses to store auto options (these are sendable to the dashboard)
	class StartingPositionSelection {
	public:
		StartingPosition _pos;
		StartingPositionSelection(StartingPosition pos);
	};
	class AutonomousTaskSelection {
	public:
		AutonomousTask _task;
		AutonomousTaskSelection(AutonomousTask task);
	};

private:
	std::shared_ptr<frc::Command> selectedCommand;

	std::string ToString(StartingPosition pos);
	std::string ToString(AutonomousTask task);

	//Create choosers (drop-down menus) to send to dashboard
	SendableChooser<StartingPositionSelection> posChooser;
	SendableChooser<AutonomousTaskSelection> taskChooser;
};
