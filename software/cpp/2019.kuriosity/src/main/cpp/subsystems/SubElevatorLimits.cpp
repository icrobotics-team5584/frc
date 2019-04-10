#include "subsystems/SubElevatorLimits.h"
#include "Robot.h"
#include <iostream>


SubElevatorLimits::SubElevatorLimits() : Subsystem("ExampleSubsystem") {

  limitBottom = Robot::_robotMap->subElevatorLimitBottom;
  limitTop = Robot::_robotMap->subElevatorLimitTop;

}

void SubElevatorLimits::InitDefaultCommand() {}

void SubElevatorLimits::Periodic(){
  //cout << "ELEVATOR LIMITS PERIODIC" << endl;
  //AutoStopBottom();
  //AutoStopTop();
  //Limit testing
  outCount++;
  if(outCount > 10){
    //SmartDashboard::PutBoolean("ELEVATOR Top Limit", GetTopLimit());
    //SmartDashboard::PutBoolean("ELEVATOR Bottom Limit", GetBottomLimit());
    outCount = 0;
  }
}

bool SubElevatorLimits::GetBottomLimit(){
    return not(limitBottom->Get());
}

bool SubElevatorLimits::GetTopLimit(){
    return limitTop->Get();
}

bool SubElevatorLimits::GetBothLimits(){
  return GetBottomLimit() || GetTopLimit();
}

void SubElevatorLimits::AutoStopTop() {
  if (GetTopLimit()){
    cout << "top" << endl;
    Robot::subElevator->PIDDisable();
  }
}

void SubElevatorLimits::AutoStopBottom() {
  if (GetBottomLimit()){
    cout << "bottom" << endl;
    Robot::subElevator->PIDDisable();
  }
}

