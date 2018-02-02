#include "AutonomousSelector.h"

AutonomousSelector::AutonomousSelector() {
	selectedCommand.reset(new CmdAuto_Nothing());
}

std::string AutonomousSelector::DetermineRoutine(StartingPosition pos, AutonomousTask task, GameData data) {
	/*
	 *
	 * Build a string from start pos, game data, and auto task,
	 *
	 * String example: "Left-Switch-Right", means start at the left, and go for the right
	 * side of the switch
	 *
	 * Alternate routines include "Both-Left", which means go for both the switch and the
	 * scale on the left side (also applies to right side) and "Nothing", which will not
	 * move the robot at all.
	 *
	 */

	//Create a strings to store elements of our routine
	std::string routine;
	std::string _data;
	std::string _pos = ToString(pos);
	std::string _task = ToString(task);

	//If going for both, check that gameData lines up with start position
	if ( _task == "Both" ) {
		if (data.GetScale() == data.GetSwitch() && data.GetScale() == _pos) {
			if (data.GetScale() == "Left") {
				routine = "Both-Left";
			} else /* if data.GetScale() == "Right" */ {
				routine = "Both-Right";
			}
		} else {
			//gameData doesn't line up with start position, we can't do both
			//do a switch routine instead
			_task = "Switch";
		}
	}

	//If going for just one thing, figure out which
	if ( (_task == "Switch") or (_task == "Scale") ){
		//Append elements of the routine
		routine.append( _pos );
		routine.append( _task );
		//Determine whether to use switch or scale GameData
		if ( _task == "Switch"){
			_data = data.GetSwitch();
		} else if ( _task == "Scale" ) {
			_data = data.GetScale();
		}
		routine.append( _data );
	}

	//if not doing anything, well.. don't do anything I guess
	if (_task == "Nothing") {
		routine = "Nothing";
	}

	return routine;
}

std::shared_ptr<frc::Command> AutonomousSelector::DetermineCommand(std::string routine){
	//Use the determined routine string and return a pointer to its associated command.
	//Annoyingly, switch case statements don't work with strings, so we're going with ifs.

	if (routine == "Left-Swtich-Left"){
		selectedCommand.reset(new CmdAuto_Left_Switch_Left() );

	}else if (routine == "Left-Swtich-Right"){
		selectedCommand.reset(new CmdAuto_Left_Switch_Right() );

	}else if (routine == "Right-Swtich-Left"){
		selectedCommand.reset(new CmdAuto_Right_Switch_Left() );

	}else if (routine == "Right-Swtich-Right"){
		selectedCommand.reset(new CmdAuto_Right_Switch_Right() );

	}else if (routine == "Middle-Swtich-Left"){
		selectedCommand.reset(new CmdAuto_Middle_Switch_Left() );

	}else if (routine == "Middle-Swtich-Right"){
		selectedCommand.reset(new CmdAuto_Middle_Switch_Right() );

	}else if (routine == "Left-Scale-Left"){
		selectedCommand.reset(new CmdAuto_Left_Switch_Left() );

	}else if (routine == "Left-Scale-Right"){
		selectedCommand.reset(new CmdAuto_Left_Scale_Right() );

	}else if (routine == "Right-Scale-Left"){
		selectedCommand.reset(new CmdAuto_Right_Scale_Left() );

	}else if (routine == "Right-Scale-Right"){
		selectedCommand.reset(new CmdAuto_Right_Scale_Right() );

	}else if ( routine == "Both-Left"){
		selectedCommand.reset(new CmdAuto_Both_Left() );

	}else if (routine == "Both-Right"){
		selectedCommand.reset(new CmdAuto_Both_Right() );

	}else /*if (routine == "Nothing")*/ {
		selectedCommand.reset(new CmdAuto_Nothing() );
	}

	return selectedCommand;
}

void AutonomousSelector::SelectAndRun(StartingPosition pos, AutonomousTask task, GameData data){
	std::string routine = DetermineRoutine(pos, task, data);
	std::shared_ptr<frc::Command> command = DetermineCommand(routine);
	command->Start();
}

void AutonomousSelector::ReadMotionProfile(std::string MP) {
	//Reading in CSV
	Robot::MPData->ReadCSV(0, MP + "/" + MP + "_left.csv");
	Robot::MPData->ReadCSV(1, MP + "/" + MP + "_right.csv");
}

std::string AutonomousSelector::ToString(StartingPosition pos){
	//Convert Starting Position Enumerator to a string
	switch(pos){
	case Left:
		return "Left";
	case Middle:
		return "Middle";
	case Right:
		return "Right";
	default:
		throw "Error: Chosen Starting Position does not exist. Look in AutonomousSelector.cpp!";
	}
}

std::string AutonomousSelector::ToString(AutonomousTask task){
	//Convert Autonomous Task Enumerator to a string
	switch(task){
	case Switch:
		return "Switch";
	case Scale:
		return "Scale";
	case Both:
		return "Both";
	case Nothing:
		return "Nothing";
	default:
		throw "Error: Chosen Autonomous Task does not exist. Look in AutonomousSelector.cpp!";
	}
}

void AutonomousSelector::SendOptionsToDashboard(){
	//Send two choosers (drop-down menus) to dashboard for auto task and start position

	//Instantiate the selection classes to send. These will be the options available to the driver
	StartingPositionSelection startLeft(Left);
	StartingPositionSelection startMiddle(Middle);
	StartingPositionSelection startRight(Right);
	AutonomousTaskSelection taskSwitch(Switch);
	AutonomousTaskSelection taskScale(Scale);
	AutonomousTaskSelection taskBoth(Both);
	AutonomousTaskSelection taskNothing(Nothing);

	//Populate choosers with the options created above
	posChooser.AddDefault("Left", startLeft);
	posChooser.AddObject("Middle", startMiddle);
	posChooser.AddObject("Right", startRight);
	taskChooser.AddDefault("Switch", taskSwitch);
	taskChooser.AddObject("Scale", taskScale);
	taskChooser.AddObject("Both", taskBoth);
	taskChooser.AddObject("Nothing", taskNothing);
}


AutonomousSelector::StartingPosition AutonomousSelector::GetStartingPosition(){
	return posChooser.GetSelected()._pos;
}

AutonomousSelector::AutonomousTask AutonomousSelector::GetAutonomousTask(){
	return taskChooser.GetSelected()._task;
}

//Below is the body of the two subclasses, StartingPositionSelection and AutonomousTaskSelection
AutonomousSelector::StartingPositionSelection::StartingPositionSelection(StartingPosition pos){
	//Constructor of StartingPositionSelection
	_pos = pos;
}

AutonomousSelector::AutonomousTaskSelection::AutonomousTaskSelection(AutonomousTask task){
	//Constructor of AutonomousTaskSelection
	_task = task;
}
