#include "SubDriveBase.h"
#include "Commands/MyJoystickDrive.h"
#include "Commands/CmdGyroDrive.h"
#include <SmartDashboard/SmartDashboard.h>
#include <math.h>

//PID constants
const static double turnP = 0.014;
const static double turnI = 0;
const static double turnD = 0;
const static double driveP = 0.25;
const static double driveI = 0.00015;
const static double driveD = 0;

//Define static objects
AHRS* SubDriveBase::navX;
double SubDriveBase::_Speed;
double SubDriveBase::_Rotation;


SubDriveBase::SubDriveBase() : frc::Subsystem("SubDriveBase"), selectedDriveMode(Manual){
	//Copy Drive wheels from RobotMap
	srxLeft = RobotMap::subDriveBaseSRXleft;
    srxRight = RobotMap::subDriveBaseSRXright;
    differentialDrive = RobotMap::subDriveBaseDifferentialDrive;

    //copy Ultrasonics from RobotMap
    ultrasonicInputFront = RobotMap::subDriveBaseUltrasonicInputFront;
    ultrasonicInputRight = RobotMap::subDriveBaseUltrasonicInputRight;
    ultrasonicInputBack = RobotMap::subDriveBaseUltrasonicInputBack;
    ultrasonicInputLeft = RobotMap::subDriveBaseUltrasonicInputLeft;

    //setup NavX PID controller
    _Rotation = 0;
    navX = RobotMap::navX.get();
	SmartDashboard::PutData("NavX", navX);
    rotationOutput = new NavxDriveRotationOutput();
    speedOutput = new NavxDriveSpeedOutput();
    distanceSource = new EncoderDistanceSource();
    turnController = new PIDController(turnP, turnI, turnD, navX, rotationOutput);
    turnController->SetInputRange(-180.0f, 180.0f);
    turnController->SetOutputRange(-1.0, 1.0);
    turnController->SetContinuous(true);
    turnController->SetAbsoluteTolerance(1);
	SmartDashboard::PutData("turnController", turnController);

    //Setup encoder PID controller
	_Speed = 0;
	relativeZero = 0;
	driveController = new PIDController(driveP, driveI, driveD, distanceSource, speedOutput);
    driveController->SetInputRange(-10, 10);
    driveController->SetOutputRange(-1,1);
    SmartDashboard::PutData("driveController", driveController);
}

void SubDriveBase::InitDefaultCommand() {
	SetDefaultCommand(new MyJoystickDrive());
}

void SubDriveBase::Periodic() {

	//code for DIO echo ultrasonic sensors
	if (++_Ultraloops >= 30) {
		ultrasonicInputFront->SetAutomaticMode(true);
		ultrasonicInputRight->SetAutomaticMode(true);
		ultrasonicInputBack->SetAutomaticMode(true);
		ultrasonicInputFront->SetAutomaticMode(true);
		frontUValue = ultrasonicInputFront->GetRangeInches();
		rightUValue = ultrasonicInputRight->GetRangeInches();
		backUValue = ultrasonicInputBack->GetRangeInches();
		leftUValue = ultrasonicInputLeft->GetRangeInches();

		frc::SmartDashboard::PutNumber("Ultra, front", frontUValue);
		frc::SmartDashboard::PutNumber("Ultra, right", rightUValue);
		frc::SmartDashboard::PutNumber("Ultra, back", backUValue);
		frc::SmartDashboard::PutNumber("Ultra, left", leftUValue);

		_Ultraloops = 0;
	}

	SmartDashboard::PutNumber("PID Speed", _Speed);
	SmartDashboard::PutNumber("PID Rotation", _Rotation);
	SmartDashboard::PutNumber("EncoderDistanceSource", GetEncoderDistance());
	SmartDashboard::PutNumber("Left enc", srxLeft->GetSelectedSensorPosition(0));
	SmartDashboard::PutNumber("Right enc", srxRight->GetSelectedSensorPosition(0));

	if (selectedDriveMode == Autonomous){
		HandlePIDOutput(_Speed, _Rotation);
	}
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

void SubDriveBase::HandlePIDOutput(double xSpeed, double zRotation){
	//Run outputs from driveController and turnController
	bool isQuickTurn;
	if (xSpeed == 0){
		isQuickTurn = true;
	} else {
		isQuickTurn = false;
	}
	differentialDrive->CurvatureDrive(xSpeed, zRotation, isQuickTurn);
}

void SubDriveBase::GyroRotate(double angle, bool relative){
	//Target a specific angle
	if (relative){
		angle = GetAngle() + angle;
	}
	turnController->SetSetpoint(angle);
	turnController->Enable();
}

void SubDriveBase::GyroDrive(double distance){
	//Target a specific displacement
	ZeroEncoders();
	driveController->SetSetpoint(distance);
	driveController->Enable();
}

bool SubDriveBase::ReachedSetPoint(){
	//Has the robot reached it's angle and distance PID setpoints?
	if (turnController->OnTarget() and driveController->OnTarget()){
		return true;
	} else {
		return false;
	}
}

void SubDriveBase::SetPIDSpeed(double speed){
	//_Speed is used as the forwards velocity when under Autonomous PID control
	_Speed = speed;
}

void SubDriveBase::SetPIDRotation(double rotation){
	//_Rotation is used as the speed of z rotation when under Autonomous PID control
	_Rotation = rotation;
}

void SubDriveBase::ZeroNavX(){
	navX->Reset();
}

double SubDriveBase::GetAngle(){
	return navX->GetAngle();
}

//void SubDriveBase::SetEncodersToRelativeZero(){
//	/*
//	 * THIS DOESN'T ZERO THE ENCODERS
//	 * It only remembers the current position and uses that as an effective zero when the
//	 * GetRelativeDisplacement() function is called. for example, the robot might be
//	 * in the middle of the field when this is called, setting relative zero to 5584.123,
//	 * the robot then drives to position 6000, GetRelativeDisplacement() will then return
//	 * 415.877 (= 6000-5584.123). This is a non-destructive method of getting the current
//	 * position that allows us to use the total encoder movement later on.
//	 */
//	relativeZero = srxLeft->GetSelectedSensorPosition(0);
//}
//
//double SubDriveBase::GetRelativeDisplacement(){
//	//Return displacement relative to position where SetEncodersToRelativeZero() was called
//	double leftSensorUnits = (srxLeft->GetSelectedSensorPosition(0) - relativeZero);
//	double rightSensorUnits = (srxRight->GetSelectedSensorPosition(0) - relativeZero);
//	double aveSensorUnits = (leftSensorUnits + rightSensorUnits) / 2;
//	double rotations = (aveSensorUnits / sensorUnitsPerRotation);
//	double meters = (rotations * wheelCircumference);
//	return meters;
//}

void SubDriveBase::ZeroEncoders(){
	srxLeft->SetSelectedSensorPosition(0,0,10);
	srxRight->SetSelectedSensorPosition(0,0,10);
}

double SubDriveBase::GetEncoderDistance(){
	double leftSensorUnits = (srxLeft->GetSelectedSensorPosition(0));
	double rightSensorUnits = (-srxRight->GetSelectedSensorPosition(0));
	double aveSensorUnits = (leftSensorUnits + rightSensorUnits) / 2;
	double rotations = (aveSensorUnits / sensorUnitsPerRotation);
	double meters = (rotations * wheelCircumference);
	return meters;
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
	double boost = (((sticky->GetRawAxis(2)+3))/4);
	differentialDrive->ArcadeDrive(-sticky->GetY() * boost, sticky->GetX() * boost);
}

void SubDriveBase::ZeroDriveEncoders(){
	sRXright->SetSelectedSensorPosition(0, 0, 10);
	sRXleft->SetSelectedSensorPosition(0, 0, 10);
}

void SubDriveBase::ClearMPBuffers(){
	sRXright->ClearMotionProfileTrajectories();
	sRXleft->ClearMotionProfileTrajectories();
}
