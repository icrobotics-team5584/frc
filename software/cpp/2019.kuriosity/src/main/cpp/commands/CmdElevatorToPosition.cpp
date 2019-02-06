#include "commands/CmdElevatorToPosition.h"
#include <iostream>

CmdElevatorToPosition::CmdElevatorToPosition(int height) {
  // Use Requires() here to declare subsystem dependencies
  Requires(Robot::subElevator.get());
  switch(height){
    case 0: 
      _height = 0.0;
    break;
    case 1:
      _height = 2.0;
    break;
  }
}

// Called just before this Command runs the first time
void CmdElevatorToPosition::Initialize() {
  cout << "CMDELEVATOR INIT" << endl;
  Robot::subElevator->TestingPID();
}

// Called repeatedly when this Command is scheduled to run
void CmdElevatorToPosition::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool CmdElevatorToPosition::IsFinished() { 
  return true;
}

// Called once after isFinished returns true
void CmdElevatorToPosition::End() {
  
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdElevatorToPosition::Interrupted() {
  End();
}
