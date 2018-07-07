#include "AutonomousSelector.h"


AutonomousSelector::AutonomousSelector() {
	/*
	 * Throw autonomous options to the DashBoard
	 */

	//setup positionSelector
	positionSelector.reset(new SendableChooser<StartingPosition>);
	positionSelector->AddObject("Left", spLeft);
	positionSelector->AddObject("Middle", spMid);
	positionSelector->AddObject("Right", spRight);

	//Send positionSelector to the DashBoard
	SmartDashboard::PutData("Starting Position", positionSelector.get());
}


std::shared_ptr<Command> AutonomousSelector::DetermineRoutine(GameData gameData) {
	/*
	 * Uses the game data from the FMS and the robot starting position selected from the Smart DashBoard
	 * to determine which command group should be run during autonomous. The selected command is returned
	 * as a shared pointer.
	 *
	 * how to get starting position: "positionSelector->GetSelected();"
	 * 		Will return startLeft, startMiddle, or startRight
	 *
	 * how to get switch game data: "gameData.GetSwitch()"
	 * 		Will return GameData::targetLeft or GameData::targetRight
	 */

	std::shared_ptr<Command> autoCommand;
	switch(positionSelector->GetSelected()) {

	case startLeft:
		if (gameData.GetSwitch() == GameData::targetLeft)
		{
			autoCommand.reset(new CmdLeftSwitchLeft);
		}
		else
		{
			autoCommand.reset(new CmdBaseLine);
		}
		break;

	case startMiddle:
		if (gameData.GetSwitch() == GameData::targetLeft)
		{
			autoCommand.reset(new CmdMiddleSwitchLeft);
		}
		else
		{
			autoCommand.reset(new CmdMiddleSwitchRight);
		}
		break;

	case startRight:
		if (gameData.GetSwitch() == GameData::targetLeft)
		{
			autoCommand.reset(new CmdBaseLine);
		}
		else
		{
			autoCommand.reset(new CmdRightSwitchRight);
		}
		break;

	}


	//TODO: Add logic to select an auto command based on gameData and startingPosition
	autoCommand.reset(new CmdMiddleSwitchLeft);


	return autoCommand;
}
