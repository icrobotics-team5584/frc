#include "subsystems/SubGimble.h"
#include "Robot.h"

SubGimble::SubGimble() : Subsystem("ExampleSubsystem") {

  _srxGimble = Robot::_robotMap->srxGimble;
  _anaGimblePot = Robot::_robotMap->subGimblePot;
  //_potSourcePID = new PIDPot();
  //_gimblePID = new gimblePID();

  //gimbleController = new PIDController(PIDp, PIDi, PIDd, _potSourcePID, _srxGimble.get());
  //gimbleController->SetSetpoint(PotCentre);
	//gimbleController->SetInputRange(PotRight, PotLeft);
	//gimbleController->SetOutputRange(-rotateSpeed, rotateSpeed); //Gimble MAX power set here
	//gimbleController->SetContinuous(false);
	//gimbleController->Enable();  //This must be set to true in future
	//frc::SmartDashboard::PutData("Arm PID Controls", gimbleController);  
  SmartDashboard::PutNumber("Gimble PIDP", PIDp);
  SmartDashboard::PutNumber("Gimble PIDI", PIDi);
  SmartDashboard::PutNumber("Gimble PIDD", PIDd);
  SmartDashboard::PutNumber("TARGET Value", target);
  SmartDashboard::PutBoolean("Test Mode", testMode);
}

void SubGimble::Periodic() {
  lc++;
	if( lc > 10){
    //SmartDashboard::PutNumber("ARM PID OUTPUT", gimbleController->Get());
	  SmartDashboard::PutNumber("POT Value Average", _anaGimblePot->GetAverageValue());
	  //SmartDashboard::PutNumber("The custom value thing", _potSourcePID->PIDGet());
	  SmartDashboard::PutNumber("ARM TALON OUTPUT %", _srxGimble->Get());
    
    lc = 0;
  }
  PIDp = SmartDashboard::GetNumber("Gimble PIDP", 0.0025);
  PIDi = SmartDashboard::GetNumber("Gimble PIDI", 0.0);
  PIDd = SmartDashboard::GetNumber("Gimble PIDD", 0.0);
  testMode = SmartDashboard::GetBoolean("Test Mode", false);
  if (testMode == true){
    target = SmartDashboard::GetNumber("TARGET Value", PotCentre);
  }
  kP = PIDp;
  kI = PIDi;
  kD = PIDd;
  CustomPID(_anaGimblePot->GetAverageValue());
}

void SubGimble::InitDefaultCommand() {}

void SubGimble::OverridePID(bool leftRight) { //true = left  ... rotate left
  if (leftRight){
    humanOffset = -1;
  }
  else{
    humanOffset = 1;
  }
  target = target + humanOffset;
  //gimbleController->SetSetpoint(target + humanOffset);
}

void SubGimble::Override(std::shared_ptr<Joystick> rightStick){
  _axis4 = rightStick->GetRawAxis(4); 

	if (_axis4 > 0.5) { 
    if((Robot::subGimbleLimits->GetRightLimit()) == false)
    {
		  OverridePID(false);
    }
	} else if (_axis4 < -0.5){ 
    if((Robot::subGimbleLimits->GetLeftLimit()) == false)
    {
      OverridePID(true);
    }
	}
}

void SubGimble::PIDGimbleTo(double angle) {
  
  potRange = PotRight - PotLeft;
  angle = angle + 90; // converts -90, 0, 90 to 0, 90, 180
  double conversion = potRange/180;
  target = (angle * conversion) + PotLeft;

	

	//gimbleController->SetSetpoint(target);
}

void SubGimble::PIDGimbleToLeft(){
  //gimbleController->SetSetpoint(PotLeft);
  target = PotLeft;
}

void SubGimble::PIDGimbleToRight(){
  //gimbleController->SetSetpoint(PotRight);
  target = PotRight;
}

void SubGimble::VoltageControl(double percentage){
  _srxGimble->Set(percentage);
}

void SubGimble::stop(int side) {
  switch(side){
    case 0:
      //gimbleController->SetSetpoint((_anaGimblePot->GetAverageValue() + 0));
      target = _anaGimblePot->GetAverageValue() + 0;
    break;
    case 1:
      //gimbleController->SetSetpoint((_anaGimblePot->GetAverageValue() - 80));
      target = _anaGimblePot->GetAverageValue() - 0;
    break;
    case 2:
      //gimbleController->SetSetpoint((_anaGimblePot->GetAverageValue() - 200));
      target = _anaGimblePot->GetAverageValue() - 0;
    break;
  }
}
void SubGimble::ToCentre(){
  target = PotCentre;
  //gimbleController->SetSetpoint(target);
}

double SubGimble::GetTarget(){
  return target;
}

double SubGimble::POTPosition(){
  return _anaGimblePot->GetAverageValue();
}

void SubGimble::CustomPID(double PIDIntput){
  error = PIDIntput - target;
  intergral = intergral + error;
  derivative = error - lastError;
  PIDOutput = (error * kP) + (intergral * kI) + (derivative * kD);
  if (PIDOutput > rotateSpeed){
    PIDOutput = rotateSpeed;
  }
  if (PIDOutput < -rotateSpeed){
    PIDOutput = -rotateSpeed;
  }
  _srxGimble->Set(PIDOutput);
  lastError = error;
  intergral = intergral * dampener;


}