/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SubGimble.h"
#include "Robot.h"

SubGimble::SubGimble() : Subsystem("ExampleSubsystem") {

  _srxGimble = Robot::_robotMap->srxGimble;
  _anaGimblePot = Robot::_robotMap->subGimblePot;
  _potSourcePID = new PIDPot();

  gimbleController = new PIDController(PIDp, PIDi, PIDd, _potSourcePID, _srxGimble.get());
  gimbleController->SetSetpoint(PotCentre);
	gimbleController->SetInputRange(PotLeft, PotRight);
	gimbleController->SetOutputRange(-0.5, 0.5);
	gimbleController->SetContinuous(false);
	gimbleController->Disable();
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
void SubGimble::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void SubGimble::enable() {
  gimbleController->Enable();
}

void SubGimble::disable() {
  gimbleController->Disable();
  _srxGimble->Set(0);
}

void SubGimble::OverridePID(bool leftRight) { //true = left
    if (leftRight){
    overrideTarget = _anaGimblePot->GetAverageValue() + humanOffset;
  }
  else{
    overrideTarget = _anaGimblePot->GetAverageValue() - humanOffset;
  }
  gimbleController->SetSetpoint(overrideTarget);
}

void SubGimble::stop() {
  gimbleController->SetSetpoint(_anaGimblePot->GetAverageValue());
}

void SubGimble::PIDGimbleTo(int angle) {
  potRange = PotLeft - PotRight;

  double target = potRange * ((angle + (totalAngle/2))/totalAngle) + PotRight;

	SmartDashboard::PutNumber("TARGET Value", target);

	gimbleController->SetSetpoint(target);
}