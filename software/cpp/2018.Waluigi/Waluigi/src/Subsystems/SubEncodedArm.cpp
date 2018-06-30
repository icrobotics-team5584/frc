

#include "SubEncodedArm.h"
#include "../RobotMap.h"
#include <SmartDashboard/SmartDashboard.h>
#include "../Commands/CmdArmDefault.h"

SubEncodedArm::SubEncodedArm() : Subsystem("ExampleSubsystem") {

	_talon = RobotMap::subEncodedArmTnx;
	_potMain = RobotMap::subEncodedArmPot;
	_potSourcePID = new PIDPot();

	armController = new PIDController(-0.0007, 0.0, 0.0, _potSourcePID, _talon.get());
	armController->SetSetpoint(1249);
	armController->SetInputRange(152, 2346);
	armController->SetOutputRange(-0.7, 0.7);
	armController->SetContinuous(false);
	armController->Disable();
	frc::SmartDashboard::PutData("Arm PID Controls", armController);

}

void SubEncodedArm::Periodic() {

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

	double target = spec * ((angle + (totalAngle/2))/totalAngle)+152;

	SmartDashboard::PutNumber("TARGET Value", target);

	armController->SetSetpoint(target);


}
