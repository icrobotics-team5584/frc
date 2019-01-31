#include "subsystems/SubGimbleLimits.h"
#include "Robot.h"

SubGimbleLimits::SubGimbleLimits() : Subsystem("ExampleSubsystem") {

  limitLeft = Robot::_robotMap->subGimbleLimitLeft;  
  limitRight = Robot::_robotMap->subGimbleLimitRight;

}

void SubGimbleLimits::InitDefaultCommand() {}

void SubGimbleLimits::Periodic(){
  outCount++;
  if(outCount > 10){
    SmartDashboard::PutBoolean("GIMBLE Left Limit", GetLeftLimit());
    SmartDashboard::PutBoolean("GIMBLE Right Limit", GetRightLimit());
    outCount = 0;
  }
}

bool SubGimbleLimits::GetBothLimits(){
  if(limitLeft->Get() || limitRight->Get()){return true;}
}

bool SubGimbleLimits::GetLeftLimit(){
  if(limitLeft->Get()){return true;}
}

bool SubGimbleLimits::GetRightLimit(){
  if(limitRight->Get()){return true;}
}
