

#include "SubEncodedArm.h"
#include "../RobotMap.h"
#include <SmartDashboard/SmartDashboard.h>
#include "../Commands/CmdArmDefault.h"

SubEncodedArm::SubEncodedArm() : Subsystem("ExampleSubsystem") {

	_talon = RobotMap::subEncodedArmTnx;
	_potMain = RobotMap::subEncodedArmPot;

	armController = new PIDController(0.1, 0.0, 0.0, _potMain.get(), _talon.get());
	armController->SetInputRange(PotBack, PotFront);
	armController->SetOutputRange(-0.7, 0.7);
	armController->SetContinuous(false);
	armController->Enable();
	SmartDashboard::PutData("Arm PID Controls", armController);

}

void SubEncodedArm::Periodic() {

	lc++;
	if( lc > 10){
		SmartDashboard::PutNumber("POT Value", _potMain->GetValue());
		SmartDashboard::PutNumber("POT Voltage", _potMain->GetVoltage());
		SmartDashboard::PutNumber("POT Value Average", _potMain->GetAverageValue());
		SmartDashboard::PutNumber("POT Voltage Average", _potMain->GetAverageVoltage());
		lc = 0;
	}
}

void SubEncodedArm::InitDefaultCommand() { //Default Command sets _talon to 0.0
	SetDefaultCommand(new CmdArmDefault());
}

void SubEncodedArm::ArmJoyMove(std::shared_ptr<frc::Joystick> controller) { //Override control for the arm
	_axis5 = controller->GetRawAxis(5); //up down control axis
	double speed = 0.0;
	speed = _axis5/4;
	_talon->Set(speed);
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

void SubEncodedArm::PIDArmTo(int angle) { //PID to a POT value given angle

	double spec = PotFront- PotBack;

	double target = spec * ((angle + (totalAngle/2))/totalAngle)+152;

	SmartDashboard::PutNumber("TARGET Value", target);

	armController->SetSetpoint(target);
}







