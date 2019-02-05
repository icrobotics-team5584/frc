#include "subsystems/SubElevatorLimits.h"
#include "Robot.h"

SubElevatorLimits::SubElevatorLimits() : Subsystem("ExampleSubsystem") {

  limitBottom = Robot::_robotMap->subElevatorLimitBottom;
  limitTop = Robot::_robotMap->subElevatorLimitTop;

}

void SubElevatorLimits::InitDefaultCommand() {}

void SubElevatorLimits::Periodic(){
  //Limit testing
  outCount++;
  if(outCount > 10){
    SmartDashboard::PutBoolean("ELEVATOR Left Limit", GetTopLimit());
    SmartDashboard::PutBoolean("ELEVATOR Right Limit", GetBottomLimit());
    outCount = 0;
  }
}

bool SubElevatorLimits::GetBottomLimit(){
    return limitBottom->Get();
}

bool SubElevatorLimits::GetTopLimit(){
    return limitTop->Get();
}


