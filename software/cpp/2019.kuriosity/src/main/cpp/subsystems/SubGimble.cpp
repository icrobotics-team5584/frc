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
  PIDp = SmartDashboard::GetNumber("Gimble PIDP", PIDp, 0.0025);
  PIDi = SmartDashboard::GetNumber("Gimble PIDI", PIDi, 0.0);
  PIDd = SmartDashboard::GetNumber("Gimble PIDD", PIDd, 0.0);
  target = SmartDashboard::GetNumber("TARGET Value", target, PotCentre);
  kP = PIDp;
  kI = PIDi;
  kD = PIDd;
  CustomPID(_anaGimblePot->GetAverageValue());
}

void SubGimble::InitDefaultCommand() {}

void SubGimble::OverridePID(bool leftRight) { //true = left  ... rotate left
  if (leftRight){
    humanOffset = -10;
  }
  else{
    humanOffset = 10;
  }

  //gimbleController->SetSetpoint(target + humanOffset);
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
}

void SubGimble::PIDGimbleToRight(){
  //gimbleController->SetSetpoint(PotRight);
}

void SubGimble::VoltageControl(double percentage){
  _srxGimble->Set(percentage);
}

void SubGimble::stop(int side) {
  switch(side){
    case 0:
      //gimbleController->SetSetpoint((_anaGimblePot->GetAverageValue() + 0));
    break;
    case 1:
      //gimbleController->SetSetpoint((_anaGimblePot->GetAverageValue() - 80));
    break;
    case 2:
      //gimbleController->SetSetpoint((_anaGimblePot->GetAverageValue() - 200));
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

void SubGimble::OverrideMotorLeft(){
  _srxGimble->Set(0.5);
}

void SubGimble::OverrideMotorRight(){
  _srxGimble->Set(-0.5);
}

void SubGimble::MotorStop(){
  _srxGimble->Set(0.0);
}

void SubGimble::PIDEnable(){
  //gimbleController->Enable();
}

void SubGimble::PIDDisable(){
  //gimbleController->Disable();
}

void SubGimble::CustomPID(double PIDIntput){
  error = PIDIntput - target;
  intergral = error + lastError;
  derivative = error - lastError;
  PIDOutput = (error * kP) + (intergral * kI) + (derivative * kD);
  if (PIDOutput > 1){
    PIDOutput = 1;
  }
  if (PIDOutput < -1){
    PIDOutput = -1;
  }
  _srxGimble->Set(PIDOutput);
  lastError = error;
  intergral = intergral * dampener;


}