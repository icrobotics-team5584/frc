#include "AutonomousSelector.h"

AutonomousSelector::AutonomousSelector() {
	autonomousTask = static_cast<Task>( SmartDashboard::GetNumber("intAutonomousTask", 0) );
}

std::string AutonomousSelector::DetermineMotionProfile(StartingPos pos){
	//Pick a task to do: Switch, Scale, Both, or Nothing.
	//Then return a string that looks like: startingPos-task-GameData.
	//eg: return "L-S-R" (start = Left, task = switch, gameData = Right)
	switch(autonomousTask){
	case Nothing:
		MPName = "Nothing";
		break;

	case Switch:
		switch(gameData.GetSwitch()){
		case GameData::L:
			MPName = pos + "-S-L";	//Append starting position to MP name
			break;
		case GameData::R:
			MPName = pos + "-S-R";
			break;
		}
		break;

	case Scale:
		switch(gameData.GetScale()){
		case GameData::L:
			MPName = pos + "-C-L";
			break;
		case GameData::R:
			MPName = pos + "-C-R";
			break;
		}
		break;

	case Both:
		//Does the gameData line up with our stating pos allowing us to actually do both?
		if ( (gameData.GetSwitch() == gameData.GetScale()) == pos){
			//Yes we can do both
			//Which side?
			if ( (gameData.GetSwitch() && gameData.GetScale()) == GameData::L){
				MPName = pos + "-B-L";
			} else {
				MPName = pos + "-B-R";
			}
		} else {
			//No, we can't do both
			//Which switch do you go for instead?
			if (gameData.GetSwitch() == GameData::L){
				MPName = pos + "-S-L";
			} else {
				MPName = pos + "-S-R";
			}
		}
	}
	return MPName;
}
