#include "subsystems/SubGimble.h"
#include "Robot.h"

SubGimble::SubGimble() : Subsystem("ExampleSubsystem") {

  _srxGimble = Robot::_robotMap->srxGimble;
  _anaGimblePot = Robot::_robotMap->subGimblePot;
  _potSourcePID = new PIDPot();
  _gimblePID = new gimblePID();

  gimbleController = new PIDController(PIDp, PIDi, PIDd, _potSourcePID, _srxGimble.get());
  gimbleController->SetSetpoint(PotCentre);
	gimbleController->SetInputRange(PotRight, PotLeft);
	gimbleController->SetOutputRange(-rotateSpeed, rotateSpeed); //Gimble MAX power set here
	gimbleController->SetContinuous(false);
	gimbleController->Enable();  //This must be set to true in future
	frc::SmartDashboard::PutData("Arm PID Controls", gimbleController);  
  
}

void SubGimble::Periodic() {
  lc++;
	if( lc > 10){
    SmartDashboard::PutNumber("ARM PID OUTPUT", gimbleController->Get());
	  SmartDashboard::PutNumber("POT Value Average", _anaGimblePot->GetAverageValue());
	  SmartDashboard::PutNumber("The custom value thing", _potSourcePID->PIDGet());
	  SmartDashboard::PutNumber("ARM TALON OUTPUT %", _srxGimble->Get());
    
    lc = 0;
  }
}

void SubGimble::InitDefaultCommand() {}

void SubGimble::enable() {
  gimbleController->Enable();
}

void SubGimble::disable() {
  gimbleController->Disable();
  _srxGimble->Set(0);
}

void SubGimble::OverridePID(bool leftRight) { //true = left  ... rotate left
  if (leftRight){
    humanOffset = humanOffset - overrideSpeed;
  }
  else{
    humanOffset = humanOffset + overrideSpeed;
  }
  if (target + humanOffset < PotLeft){
    humanOffset = target - PotLeft;
  }
  if (target + humanOffset > PotRight){
    humanOffset = PotRight - target;
  }
  gimbleController->SetSetpoint(target + humanOffset);
}

void SubGimble::Override(std::shared_ptr<Joystick> rightStick){
  _axis4 = rightStick->GetRawAxis(4); 

	if (_axis4 > 0.5) { 
		OverridePID(false);
	} else if (_axis4 < -0.5){ 
    OverridePID(true);
	}
}

void SubGimble::PIDGimbleTo(double angle) {
  
  potRange = PotRight - PotLeft;
  angle = angle + 90; // converts -90, 0, 90 to 0, 90, 180
  double conversion = potRange/180;
  target = (angle * conversion) + PotLeft;

	SmartDashboard::PutNumber("TARGET Value", target);

	gimbleController->SetSetpoint(target);
}

void SubGimble::PIDGimbleToLeft(){
  gimbleController->SetSetpoint(PotLeft);
}

void SubGimble::PIDGimbleToRight(){
  gimbleController->SetSetpoint(PotRight);
}

void SubGimble::VoltageControl(double percentage){
  _srxGimble->Set(percentage);
}

void SubGimble::stop(int side) {
  switch(side){
    case 0:
      gimbleController->SetSetpoint((_anaGimblePot->GetAverageValue() + 0));
    break;
    case 1:
      gimbleController->SetSetpoint((_anaGimblePot->GetAverageValue() - 80));
    break;
    case 2:
      gimbleController->SetSetpoint((_anaGimblePot->GetAverageValue() - 200));
  }
}
void SubGimble::ToCentre(){
  target = PotCentre;
  gimbleController->SetSetpoint(target);
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
  gimbleController->Enable();
}

void SubGimble::PIDDisable(){
  gimbleController->Disable();
}