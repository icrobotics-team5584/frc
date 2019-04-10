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
    
    //SmartDashboard::PutBoolean("GIMBLE Left Limit", GetLeftLimit());
    //SmartDashboard::PutBoolean("GIMBLE Right Limit", GetRightLimit());
    outCount = 0;
  }
}

bool SubGimbleLimits::GetBothLimits(){
  if(limitLeft->Get() || limitRight->Get()){
    return true;
    }else{
      return false;
    }
}

bool SubGimbleLimits::GetLeftLimit(){
  return not(limitLeft->Get());
  std::cout << limitLeft->Get() << std::endl;
}

bool SubGimbleLimits::GetRightLimit(){
  return not(limitRight->Get());
  std::cout << limitRight->Get() << std::endl;
}
