#include "commands/CmdElevatorToPosition.h"
#include <iostream>

CmdElevatorToPosition::CmdElevatorToPosition(bool bottom1, bool goTo, int setTo) {
  // Use Requires() here to declare subsystem dependencies
  Requires(Robot::subElevator.get());
 // _height = 0.0;
 // Robot::subElevator->ElevatorToPos(_height);
  bottom = bottom1;
  goTo = goTo;
  setTo = setTo;
  

}

// Called just before this Command runs the first time
void CmdElevatorToPosition::Initialize() {
  //cout << "CMDELEVATOR INIT" << endl;// comment for when 
  _height = Robot::subElevator->GetHeight();

  if(bottom == true){
      Robot::subElevator->SetHeight(BOTTOM_HATCH);
      //timeRound = 1;
      cout << "000000000000000" << endl;
  }
  if (bottom == false)
  {

    //if(goTo){
    //  timeRound = setTo;
    //  cout << "sssseeeeeeeeeeeeeeeeettttttttt" << endl;
    //}else{
      
      
     // bool onlyOnce = false;

      //if(_height == 3.3 && onlyOnce == false){
      //  _height = 0.0;
      //  onlyOnce = true;
      //  }
      //if(_height == 2.6 && onlyOnce == false){
      //  _height = 3.3;
      //  onlyOnce = true;
      //}
      //if(_height == 1.4 && onlyOnce == false){
      //  _height = 2.6;
      //  onlyOnce = true;
      //}
      //if(_height == 0.0 && onlyOnce == false){
      //  _height = 1.4;
      //  onlyOnce = true;
      //}
      
      
      //Gets current height and moves up to the next height(Accept from top postion)
      //From top postion it goes back to bottom postion
     switch(_height){
       case BOTTOM_HATCH: 
         Robot::subElevator->SetHeight(BOTTOM_CARGO);
       break;
       case BOTTOM_CARGO:
         Robot::subElevator->SetHeight(MID_HATCH);
       break;
       case MID_HATCH:
         Robot::subElevator->SetHeight(MID_CARGO);
       break;
       case MID_CARGO:
         Robot::subElevator->SetHeight(TOP_HATCH);
       break;
       case TOP_HATCH:
         Robot::subElevator->SetHeight(TOP_CARGO);
       break;
       case TOP_CARGO:
         Robot::subElevator->SetHeight(BOTTOM_HATCH);
       break; 
     }
     cout << "cccccaaaaasssssseeeeeeee" << endl;
     timeRound++;

     if(timeRound > 3){
       timeRound = 0;
       cout << "timeROUND >>>>>>>>>>>>>>>>> 3 " << endl;
     }

    

  }


  //Robot::subElevator->TestingPID();
  
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
