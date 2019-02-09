#include "subsystems/SubGimble.h"
#include "Robot.h"

SubGimble::SubGimble() : Subsystem("ExampleSubsystem") {

  _srxGimble = Robot::_robotMap->srxGimble;
  _anaGimblePot = Robot::_robotMap->subGimblePot;
  _potSourcePID = new PIDPot();

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
  //  if (leftRight){
  //  overrideSpeed = overrideSpeed + humanOffset;
  //}
  //else{
  //  overrideSpeed = overrideSpeed + - humanOffset;
  //}
  //gimbleController->SetSetpoint(overrideTarget);
}

void SubGimble::PIDGimbleTo(double angle) {
  
  potRange = PotRight - PotLeft;
  angle = angle + 90; // converts -90, 0, 90 to 0, 90, 180
  double conversion = potRange/180;
  double target = (angle * conversion) + PotLeft;

	SmartDashboard::PutNumber("TARGET Value", target);

	gimbleController->SetSetpoint(target);
}

void SubGimble::stop() {
  gimbleController->SetSetpoint(_anaGimblePot->GetAverageValue());
}
void SubGimble::ToCentre(){
  gimbleController->SetSetpoint(PotCentre);
}