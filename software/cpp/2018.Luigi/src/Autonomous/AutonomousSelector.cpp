#include "AutonomousSelector.h"
#include "Robot.h"
#include "Autonomous/AutoCommandsIncludes.h"	//Include all possible autonomous commands

AutonomousSelector::AutonomousSelector() : selectedCommand(new CmdAuto_Nothing())
{
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
	std::string _pos = ToString(pos);
	std::string _task = ToString(task);

	if (_pos == "Middle") {
		routine = "Middle-Switch-";
		routine.append(data.GetSwitch());
	} else {
		routine.append(_pos);
		if(PrioritizeSwitch()){
			if (data.GetSwitch() == _pos){
				routine.append("-Switch-");
				routine.append(data.GetSwitch());
			} else {
				routine = CrossOrStayAway(routine, _pos, data);
			}
		} else {
			if (data.GetScale() == _pos) {
				if (data.GetSwitch() == _pos){
					routine = "Both-";
					routine.append(_pos);
				} else {
					routine.append("-Scale-");
					routine.append(data.GetScale());
				}
			} else {
				routine = CrossOrStayAway(routine, _pos, data);
			}
		}
	}

	return routine;
}

std::string AutonomousSelector::CrossOrStayAway(std::string routineSoFar, std::string pos, GameData data){
	/*
	 * Edit the routine string to reflect whether or not we need to stay on our side of the field
	 * in the case that we are allied with another robot who wants to go for the opposite side of
	 * the scale instead of us.
	 */

	if (StayAway()){
		if (data.GetSwitch() == pos){
			routineSoFar.append("-Switch-");
			routineSoFar.append(data.GetSwitch());
			return routineSoFar;
		}
		return "Baseline";
	} else {
		routineSoFar.append("-Scale-");
		routineSoFar.append(data.GetScale());
		return routineSoFar;
	}
}

void AutonomousSelector::SetCommand(std::string routine){
	/*
	 * Use the determined routine string and return a pointer to its associated command.
	 * Annoyingly, switch case statements don't work with strings, so we're going with ifs.
	 */

	if (routine == "Left-Switch-Left"){
		selectedCommand.reset(new CmdAuto_Left_Switch_Left() );

	}else if (routine == "Left-Switch-Right"){
		selectedCommand.reset(new CmdAuto_Left_Switch_Right() );

	}else if (routine == "Right-Switch-Left"){
		selectedCommand.reset(new CmdAuto_Right_Switch_Left() );

	}else if (routine == "Right-Switch-Right"){
		selectedCommand.reset(new CmdAuto_Right_Switch_Right() );

	}else if (routine == "Middle-Switch-Left"){
		selectedCommand.reset(new CmdAuto_Middle_Switch_Left() );

	}else if (routine == "Middle-Switch-Right"){
		selectedCommand.reset(new CmdAuto_Middle_Switch_Right() );

	}else if (routine == "Left-Scale-Left"){
		selectedCommand.reset(new CmdAuto_Left_Scale_Left() );

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

	}else if (routine == "Baseline"){
		selectedCommand.reset(new CmdGyroDrive(3, 0));

	}else /*if (routine == "Nothing")*/ {
		selectedCommand.reset(new CmdAuto_Nothing() );
	}
}

void AutonomousSelector::SelectAndRun(StartingPosition pos, AutonomousTask task, GameData data){
	//Determine which command to run and start it
	std::string routine = DetermineRoutine(pos, task, data);
	std::cout << "Selected routine: " << routine << std::endl;
	SetCommand(routine);
	selectedCommand->Start();
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
//	SmartDashboard::PutData("Autonomous Task", &taskChooser);

	//Send Boolean Options to dashboard
	SmartDashboard::PutBoolean("Prioritize Switch", false);
	SmartDashboard::PutBoolean("Stay out of ally's way", false);
}

bool AutonomousSelector::PrioritizeSwitch(){
	return (SmartDashboard::GetBoolean("Prioritize Switch", false));
}

bool AutonomousSelector::StayAway(){
	return (SmartDashboard::GetBoolean("Stay out of ally's way", false));
}

AutonomousSelector::StartingPosition AutonomousSelector::GetStartingPosition(){
	StartingPositionSelection* selectedStartPos;
	selectedStartPos = posChooser.GetSelected();
	return selectedStartPos->_pos;
}

AutonomousSelector::AutonomousTask AutonomousSelector::GetAutonomousTask(){
	AutonomousTaskSelection* selectedAutoTask;
	selectedAutoTask = taskChooser.GetSelected();
	return selectedAutoTask->_task;
}

//Below is the body of the two subclasses, StartingPositionSelection and AutonomousTaskSelection
AutonomousSelector::StartingPositionSelection::StartingPositionSelection(StartingPosition pos) : _pos(pos) {
	//Constructor of StartingPositionSelection
}

AutonomousSelector::AutonomousTaskSelection::AutonomousTaskSelection(AutonomousTask task) : _task(task) {
	//Constructor of AutonomousTaskSelection
}
