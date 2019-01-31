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
    cout << "GIMBLE LIMIT TO DASH" << endl;
    SmartDashboard::PutBoolean("GIMBLE Left Limit", GetLeftLimit());
    SmartDashboard::PutBoolean("GIMBLE Right Limit", GetRightLimit());
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
  cout << "GIMBLE LEFT LIMIT" << limitLeft->Get() <<  endl;
  return limitLeft->Get();
}

bool SubGimbleLimits::GetRightLimit(){
  cout << "GIMBLE RIGHT LIMIT" << limitRight->Get() << endl;
  return limitRight->Get();
}
