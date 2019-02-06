#include "commands/CmdElevatorToPosition.h"
#include <iostream>

CmdElevatorToPosition::CmdElevatorToPosition(bool bottom, bool goTo, int setTo) {
  // Use Requires() here to declare subsystem dependencies
  Requires(Robot::subElevator.get());

  bottom = bottom;
  goTo = goTo;
  setTo = setTo;
  

}

// Called just before this Command runs the first time
void CmdElevatorToPosition::Initialize() {
  cout << "CMDELEVATOR INIT" << endl;


if(bottom){
      _height = 0.0;
      //timeRound = 1;
      cout << "000000000000000" << endl;
  }else{

    if(goTo){
      timeRound = setTo;
      cout << "sssseeeeeeeeeeeeeeeeettttttttt" << endl;
    }else{

      switch(timeRound){
        case 0: 
          _height = 0.0;
        break;
        case 1:
          _height = 1.4;
        break;
        case 2:
          _height = 2.6;
        break;
        case 3:
          _height = 3.3;
        break;
      }
      cout << "cccccaaaaasssssseeeeeeee" << endl;
      timeRound++;

      if(timeRound > 3){
        timeRound = 0;
        cout << "timeROUND >>>>>>>>>>>>>>>>> 3 " << endl;
      }

    }
    

  }


  //Robot::subElevator->TestingPID();
  Robot::subElevator->ElevatorToPos(_height);
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
