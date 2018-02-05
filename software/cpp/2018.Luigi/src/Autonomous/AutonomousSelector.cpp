#include "AutonomousSelector.h"
#include "Robot.h"
#include "Autonomous/AutoCommandsIncludes.h"	//Include all possible autonomous commands

AutonomousSelector::AutonomousSelector() {
	selectedCommand.reset(new CmdAuto_Nothing());
}

std::string AutonomousSelector::DetermineRoutine(StartingPosition pos, AutonomousTask task, GameData data) {
	/*
	 * Build a string from start pos, game data, and auto task,
	 *
	 * String example: "Left-Switch-Right", means start at the left, and go for the right
	 * side of the switch
	 *
	 * Alternate routines include "Both-Left", which means go for both the switch and the
	 * scale on the left side (also applies to right side) and "Nothing", which will not
	 * move the robot at all.
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
		routine.append( _pos  + "-");
		routine.append( _task  + "-");
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

	std::cout << "Detemining auto routine: " << routine << std::endl;
	return routine;
}

std::shared_ptr<frc::Command> AutonomousSelector::DetermineCommand(std::string routine){
	/*
	 * Use the determined routine string and return a pointer to its associated command.
	 * Annoyingly, switch case statements don't work with strings, so we're going with ifs.
	 */

	std::shared_ptr<frc::Command> commandToSelect;

	if (routine == "Left-Swtich-Left"){
		commandToSelect.reset(new CmdAuto_Left_Switch_Left() );

	}else if (routine == "Left-Swtich-Right"){
		commandToSelect.reset(new CmdAuto_Left_Switch_Right() );

	}else if (routine == "Right-Swtich-Left"){
		commandToSelect.reset(new CmdAuto_Right_Switch_Left() );

	}else if (routine == "Right-Swtich-Right"){
		commandToSelect.reset(new CmdAuto_Right_Switch_Right() );

	}else if (routine == "Middle-Swtich-Left"){
		commandToSelect.reset(new CmdAuto_Middle_Switch_Left() );

	}else if (routine == "Middle-Swtich-Right"){
		commandToSelect.reset(new CmdAuto_Middle_Switch_Right() );

	}else if (routine == "Left-Scale-Left"){
		commandToSelect.reset(new CmdAuto_Left_Switch_Left() );

	}else if (routine == "Left-Scale-Right"){
		commandToSelect.reset(new CmdAuto_Left_Scale_Right() );

	}else if (routine == "Right-Scale-Left"){
		commandToSelect.reset(new CmdAuto_Right_Scale_Left() );

	}else if (routine == "Right-Scale-Right"){
		commandToSelect.reset(new CmdAuto_Right_Scale_Right() );

	}else if ( routine == "Both-Left"){
		commandToSelect.reset(new CmdAuto_Both_Left() );

	}else if (routine == "Both-Right"){
		commandToSelect.reset(new CmdAuto_Both_Right() );

	}else /*if (routine == "Nothing")*/ {
		commandToSelect.reset(new CmdAuto_Nothing() );
	}
	return commandToSelect;
}

void AutonomousSelector::SelectAndRun(StartingPosition pos, AutonomousTask task, GameData data){
	std::string routine = DetermineRoutine(pos, task, data);	//Pick an autonomous routine based on inputs
	selectedCommand = DetermineCommand(routine);				//Determine which command to run
	std::cout << "about to run routine: " << routine << std::endl;
	selectedCommand->Start();									//Start the command
}

void AutonomousSelector::StopAutoCommand(){
	//stop the command that started in AutonomousSelector::SelectAndRun(...)
	selectedCommand->Cancel();
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

	//Populate position chooser with options
	posChooser.AddDefault("Left", new StartingPositionSelection(Left));
	posChooser.AddObject("Middle", new StartingPositionSelection(Middle));
	posChooser.AddObject("Right", new StartingPositionSelection(Right));

	//Populate position chooser with options
	taskChooser.AddDefault("Switch", new AutonomousTaskSelection(Switch));
	taskChooser.AddObject("Scale", new AutonomousTaskSelection(Scale));
	taskChooser.AddObject("Both", new AutonomousTaskSelection(Both));
	taskChooser.AddObject("Nothing", new AutonomousTaskSelection(Nothing));

	//Send choosers to dashboard
	SmartDashboard::PutData("Starting Position", &posChooser);
	SmartDashboard::PutData("Autonomous Task", &taskChooser);
}


AutonomousSelector::StartingPosition AutonomousSelector::GetStartingPosition(){
	StartingPositionSelection* selectedStartPos;
	selectedStartPos = posChooser.GetSelected();
	std::cout << "Getting start pos: " << selectedStartPos->_pos << std::endl;
	return selectedStartPos->_pos;
}

AutonomousSelector::AutonomousTask AutonomousSelector::GetAutonomousTask(){
	AutonomousTaskSelection* selectedAutoTask;
	selectedAutoTask = taskChooser.GetSelected();
	std::cout << "Getting auto task: " << selectedAutoTask->_task << std::endl;
	return selectedAutoTask->_task;
}

//Below is the body of the two subclasses, StartingPositionSelection and AutonomousTaskSelection
AutonomousSelector::StartingPositionSelection::StartingPositionSelection(StartingPosition pos) : _pos(pos) {
	//Constructor of StartingPositionSelection
}

AutonomousSelector::AutonomousTaskSelection::AutonomousTaskSelection(AutonomousTask task) : _task(task) {
	//Constructor of AutonomousTaskSelection
}
