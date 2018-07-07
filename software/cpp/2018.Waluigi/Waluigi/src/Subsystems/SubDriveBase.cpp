


#include "ctre/Phoenix.h"


#include "SubDriveBase.h"
#include "../RobotMap.h"
#include <iostream>
#include "../Commands/CmdJoyStickDrive.h"


SubDriveBase::SubDriveBase() : frc::Subsystem("SubDriveBase") {
    tnxFrontRight = RobotMap::subDriveBaseTnxFrontRight;
    tnxFrontLeft = RobotMap::subDriveBaseTnxFrontLeft;
    difDrive = RobotMap::subDriveBaseDifDrive;
    tnxBackLeft = RobotMap::subDriveBaseTnxBackLeft;
    tnxBackRight = RobotMap::subDriveBaseTnxBackRight;
    NavX = RobotMap::subDriveBaseNavx;

    //Setup PIDController
    rotationOutput = new NavxDriveRotationOutput();
    turnController = new PIDController(0.02, 0, 0, NavX.get(), rotationOutput);
    turnController->SetInputRange(-180.0f, 180.0f);
    turnController->SetOutputRange(-0.7, 0.7);
    turnController->SetContinuous(true);
    turnController->SetAbsoluteTolerance(3);
    SmartDashboard::PutData("turncontroller", turnController);
}

void SubDriveBase::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

        SetDefaultCommand(new CmdJoyStickDrive());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

void SubDriveBase::Periodic() {
    // Put code here to be run every loop

}

void SubDriveBase::JoyStickDrive(std::shared_ptr<frc::Joystick> SunFlower){

	float Speed = -SunFlower->GetY();
	float Turn = SunFlower->GetX() - 0.1;
	difDrive->ArcadeDrive(Speed, Turn);

}

double SubDriveBase::GetEncoderDistance(){
	double gearRatio = 10.5;
	double EncoderTicsPerRotation = 80;
	double MetersPerRotation = 0.4787;

	double EncoderTics;
	EncoderTics = tnxBackLeft->GetSelectedSensorPosition(0);
	EncoderTics = EncoderTics/gearRatio;
	double WheelRotations;
	WheelRotations = EncoderTics/EncoderTicsPerRotation;
	double Theamountofmetersgoneby;
	Theamountofmetersgoneby = WheelRotations * MetersPerRotation;


	return Theamountofmetersgoneby;
}

void SubDriveBase::AutoDrive(double Speed, double Angle){

	double currentAngle = GetAngle();
	double pValue = 0.05;
	double error = Angle - currentAngle;
	double rotation = error * pValue;
std::cout << "Running at speed " << Speed << std::endl;
	difDrive->ArcadeDrive(Speed,rotation );

}

void SubDriveBase::AutoTurn(bool GoRight){
	if(GoRight==true){
		difDrive->ArcadeDrive(0,0.5);
	}
	else{
		difDrive->ArcadeDrive(0,-0.5);
	}

}

void SubDriveBase::ResetEncoder(){
	tnxBackLeft->SetSelectedSensorPosition(0.0,0.0,10);
	tnxBackRight->SetSelectedSensorPosition(0.0,0.0,10);


}

double SubDriveBase::GetAngle(){
	return NavX->GetAngle();


}

void SubDriveBase::PIDTurn(double Rotation){
	difDrive->ArcadeDrive(0,Rotation);
}

void SubDriveBase::SetSetpoint(double Setpoint){
	turnController->SetSetpoint(Setpoint);
	turnController->Enable();
}

void SubDriveBase::PIDEnd(){
	turnController->Disable();

}

bool SubDriveBase::AtSetpoint(){
	return turnController->OnTarget();
}

void SubDriveBase::ResetNavX(){
	NavX->Reset();
}
