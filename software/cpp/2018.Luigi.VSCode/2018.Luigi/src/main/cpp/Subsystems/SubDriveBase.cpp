#include "SubDriveBase.h"
#include "Commands/MyJoystickDrive.h"
#include "Commands/CmdGyroDrive.h"
#include <SmartDashboard/SmartDashboard.h>
#include <math.h>

//PID constants
const static double turnP = 0.01;
const static double turnI = 0;
const static double turnD = 0;
const static double driveP = 0.3;
const static double driveI = 0;
const static double driveD = 0;

//Define static objects

SubDriveBase::SubDriveBase() : frc::Subsystem("SubDriveBase"), selectedDriveMode(Manual){
	//Copy Drive wheels from RobotMap
	srxLeft = RobotMap::subDriveBaseSRXleft;
    srxRight = RobotMap::subDriveBaseSRXright;
    differentialDrive = RobotMap::subDriveBaseDifferentialDrive;


    //setup NavX PID controller
    _Rotation = 0;
    _isQuickTurn = false;
    navX = RobotMap::navX.get();
	SmartDashboard::PutData("NavX", navX);
    rotationOutput = new NavxDriveRotationOutput();
    speedOutput = new NavxDriveSpeedOutput();
    distanceSource = new EncoderDistanceSource();
    turnController = new PIDController(turnP, turnI, turnD, navX, rotationOutput);
    turnController->SetInputRange(-180.0f, 180.0f);
    turnController->SetOutputRange(-0.7, 0.7);
    turnController->SetContinuous(true);
    turnController->SetAbsoluteTolerance(3);
	SmartDashboard::PutData("turnController", turnController);

    //Setup encoder PID controller
	_Speed = 0;
	relativeZero = 0;
	driveController = new PIDController(driveP, driveI, driveD, distanceSource, speedOutput);
    driveController->SetOutputRange(-1,1);
    driveController->SetAbsoluteTolerance(0.1);
    SmartDashboard::PutData("driveController", driveController);
}

void SubDriveBase::InitDefaultCommand() {
	SetDefaultCommand(new MyJoystickDrive());
}

void SubDriveBase::Periodic() {


	SmartDashboard::PutNumber("EncoderDistanceSource", GetEncoderDistance());
	if (selectedDriveMode == Autonomous){
		HandlePIDOutput(_Speed, _Rotation, _isQuickTurn);
	}
}

void SubDriveBase::AutoDrive(double speed, double rotation) {
	//A basic drive with no sensor feedback
	differentialDrive->ArcadeDrive(speed, rotation);
}

void SubDriveBase::Stop(){
	//Stop the drive motors
	differentialDrive->ArcadeDrive(0,0);
	turnController->Disable();
}

void SubDriveBase::TakeJoystickInputs(std::shared_ptr<Joystick> sticky ) {
	//Drive with the Gamepad left stick, use L2 as boost
	//double boost = (((sticky->GetRawAxis(2)+3))/4);
	differentialDrive->ArcadeDrive(-sticky->GetY(), sticky->GetX());
}

void SubDriveBase::GyroRotate(double angle){
	//Target a specific angle
	turnController->SetSetpoint(angle);
}

void SubDriveBase::GyroDrive(double distance, double maxPower){
	//Target a specific displacement
	SmartDashboard::PutNumber("maxPower", maxPower);
	std::cout << "ran sd::pn(mp)" << std::endl;
	ZeroEncoders();
	driveController->SetOutputRange(-maxPower, maxPower);
	driveController->SetSetpoint(distance);
}

void SubDriveBase::ZeroNavX(){
	navX->Reset();
}

void SubDriveBase::ZeroEncoders(){
	srxLeft->SetSelectedSensorPosition(0,0,10);
	srxRight->SetSelectedSensorPosition(0,0,10);
}

void SubDriveBase::ClearMPBuffers(){
	srxRight->ClearMotionProfileTrajectories();
	srxLeft->ClearMotionProfileTrajectories();
}

void SubDriveBase::SetPIDSpeed(double speed){
	//_Speed is used as the forwards velocity when under Autonomous PID control
	_Speed = speed;
}

void SubDriveBase::SetPIDRotation(double rotation){
	//_Rotation is used as the speed of z rotation when under Autonomous PID control
	_Rotation = rotation;
}

void SubDriveBase::SetPIDIsQuickTurn(bool isQuickTurn){
	//If _isQuickTurn is set, the PIDControllers will ignore any xSpeed inputs
	_isQuickTurn = isQuickTurn;
}

void SubDriveBase::SetDrivePIDVals(double p, double i, double d){
	driveController->SetPID(p, i, d);
}

void SubDriveBase::HandlePIDOutput(double xSpeed, double zRotation, bool isQuickTurn){
	//Run outputs from driveController and turnController
	SmartDashboard::PutNumber("xSpeed", xSpeed);
	SmartDashboard::PutNumber("zRotation", zRotation);
	if (isQuickTurn) {
		xSpeed = 0;
	}
	differentialDrive->CurvatureDrive(xSpeed, zRotation, isQuickTurn);
}

void SubDriveBase::SetDriveMode(DriveMode driveMode){
	//Setup the drive base to either be controlled manually or autonomously
	//(motion profiles are separate from this, autonomous refers to local PIDControllers)
	selectedDriveMode = driveMode;

	switch(driveMode){
	case Manual:
		turnController->Disable();
		driveController->Disable();
		break;

	case Autonomous:
		turnController->Enable();
		driveController->Enable();
		break;
	}
}

bool SubDriveBase::ReachedSetPoint(){
	//Has the robot reached it's angle and distance PID setpoints?
	SmartDashboard::PutBoolean("turnController->OnTarget", turnController->OnTarget());
	SmartDashboard::PutBoolean("driveController->OnTarget", driveController->OnTarget());
	if (_isQuickTurn){
		return turnController->OnTarget();
	} else if (turnController->OnTarget() and driveController->OnTarget()){
		return true;
	} else {
		return false;
	}
}

double SubDriveBase::GetAngle(){
	return navX->GetAngle();
}

double SubDriveBase::GetEncoderDistance(){
	//Return the straight distance traveled by the robot since Zeroing the encoders
	//The return value is measured in meters.
	double leftSensorUnits = (srxLeft->GetSelectedSensorPosition(0));
	double rightSensorUnits = (-srxRight->GetSelectedSensorPosition(0));
	double aveSensorUnits = (leftSensorUnits + rightSensorUnits) / 2;
	double rotations = (aveSensorUnits / sensorUnitsPerRotation);
	double meters = (rotations * wheelCircumference);
	return meters;
}
