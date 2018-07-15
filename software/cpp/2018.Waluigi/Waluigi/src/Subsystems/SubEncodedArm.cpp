

#include "SubEncodedArm.h"
#include "../RobotMap.h"
#include <SmartDashboard/SmartDashboard.h>
#include "../Commands/CmdArmDefault.h"

SubEncodedArm::SubEncodedArm() : Subsystem("ExampleSubsystem") {

	_talon = RobotMap::subEncodedArmTnx;
	_potMain = RobotMap::subEncodedArmPot;
	_potSourcePID = new PIDPot();
	_armOutputPID = new armPID();

	armController = new PIDController(PIDp, PIDi, PIDd, _potSourcePID, _armOutputPID);
	armController->SetSetpoint(PotUp);
	armController->SetInputRange(PotBack, PotFront);
	armController->SetOutputRange(-0.7, 0.7);
	armController->SetContinuous(false);
	armController->Disable();
	frc::SmartDashboard::PutData("Arm PID Controls", armController);

}

void SubEncodedArm::Periodic() {

	// refresh dashboard (but not every time!) . . .
	lc++;
	if( lc > 10){
		//SmartDashboard::PutNumber("POT Value", _potMain->GetValue());
		//SmartDashboard::PutNumber("POT Voltage", _potMain->GetVoltage());
		SmartDashboard::PutNumber("POT Value Average", _potMain->GetAverageValue());
		//SmartDashboard::PutNumber("POT Voltage Average", _potMain->GetAverageVoltage());

		SmartDashboard::PutNumber("ARM ERROR", armController->GetError());
		SmartDashboard::PutNumber("ARM OUTPUT", armController->Get());
		SmartDashboard::PutNumber("ARM SETPOINT", armController->GetSetpoint());
		SmartDashboard::PutNumber("ARM ERROR", armController->Get());

		SmartDashboard::PutNumber("The custom value thing", _potSourcePID->PIDGet());

		lc = 0;
	}
}

void SubEncodedArm::InitDefaultCommand() { //Default Command sets _talon to 0.0
	//SetDefaultCommand(new CmdArmDefault());
}

void SubEncodedArm::ArmJoyMove(std::shared_ptr<frc::Joystick> controller) { //Override control for the arm
	_axis5 = controller->GetRawAxis(5); //up down control axis
	double speed = 0.0;
	speed = _axis5/3;
	_talon->Set(speed);
}

void SubEncodedArm::VoltageControl(double percentage) {
	_talon->Set(percentage);
}

double SubEncodedArm::GetArmAngle() {
	double value = _potMain->GetAverageValue();
	value = value - PotBack; //number of sensor units when arm is flat back
	value = value / (PotFront - PotBack); //range of sensor units from back to front
	value = value * totalAngle; //range of angles in degrees
	value = value - (totalAngle/2); //half of total range of angles in degrees
	return value;
}

void SubEncodedArm::Stop() { //Used by the default command
	_talon->Set(0.0);
}

void SubEncodedArm::PIDToggle() { //Toggles PID (armController) on/off
	if (armController->IsEnabled()) {
		armController->Disable();
	}else {
		armController->Enable();
	}
}

void SubEncodedArm::PIDEnable() {
	armController->Enable();
}

void SubEncodedArm::PIDDisable() {
	armController->Disable();
}

void SubEncodedArm::PIDArmTo(int angle) { //PID to a POT value given angle

	double spec = PotFront- PotBack;

	double target = spec * ((angle + (totalAngle/2))/totalAngle)+PotBack;

	SmartDashboard::PutNumber("TARGET Value", target);

	armController->SetSetpoint(target);

}
