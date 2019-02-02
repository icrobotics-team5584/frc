#include "subsystems/SubElevatorLimits.h"
#include "Robot.h"

SubElevatorLimits::SubElevatorLimits() : Subsystem("ExampleSubsystem") {

  limitBottom = Robot::_robotMap->subElevatorLimitBottom;
  limitTop = Robot::_robotMap->subElevatorLimitTop;

}

void SubElevatorLimits::InitDefaultCommand() {}

bool SubElevatorLimits::GetBottomLimit(){
    return limitBottom->Get();
}

bool SubElevatorLimits::GetTopLimit(){
    return limitTop->Get();
}


