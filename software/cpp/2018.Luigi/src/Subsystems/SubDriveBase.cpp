#include "SubDriveBase.h"
#include "Commands/MyJoystickDrive.h"
#include "Commands/AutonomousCommands/CmdAuto_GyroDrive.h"
#include <SmartDashboard/SmartDashboard.h>


//PID constants
const static double turnP = 0.014;
const static double turnI = 0;
const static double turnD = 0;
const static double driveP = 0.03;
const static double driveI = 0;
const static double driveD = 0;

//Define static objects
AHRS* SubDriveBase::navX;
double SubDriveBase::_Speed;
double SubDriveBase::_Rotation;


SubDriveBase::SubDriveBase() : frc::Subsystem("SubDriveBase"), selectedDriveMode(Manual){
	//Copy Drive wheels from RobotMap
	sRXleft = RobotMap::subDriveBaseSRXleft;
    sRXright = RobotMap::subDriveBaseSRXright;
    differentialDrive = RobotMap::subDriveBaseDifferentialDrive;

    //copy Ultrasonics from RobotMap
    ultrasonicInputFront = RobotMap::subDriveBaseUltrasonicInputFront;
    ultrasonicInputRight = RobotMap::subDriveBaseUltrasonicInputRight;
    ultrasonicInputBack = RobotMap::subDriveBaseUltrasonicInputBack;
    ultrasonicInputLeft = RobotMap::subDriveBaseUltrasonicInputLeft;

    //setup NavX PID controllers
    navX = RobotMap::navX.get();
    _Speed = 0;
    _Rotation = 0;
    rotationOutput = new NavxDriveRotationOutput();
    speedOutput = new NavxDriveSpeedOutput();
    distanceSource = new EncoderDistanceSource();
    turnController = new PIDController(turnP, turnI, turnD, navX, rotationOutput);
    turnController->SetInputRange(-180.0f, 180.0f);
    turnController->SetOutputRange(-1.0, 1.0);
    turnController->SetContinuous(true);
    turnController->SetAbsoluteTolerance(1);
    driveController = new PIDController(driveP, driveI, driveD, distanceSource, speedOutput);
    driveController->SetInputRange(-10, 10);
    driveController->SetOutputRange(-1,1);

	//Put NavX angle on Dashboard
	SmartDashboard::PutData("NavX", navX);
	SmartDashboard::PutData("turnController", turnController);
	SmartDashboard::PutData("driveController", driveController);
	driveModeChooser.AddDefault("Manual", new DriveModeClass(Manual));
	driveModeChooser.AddObject("Gyro", new DriveModeClass(Autonomous));
	SmartDashboard::PutData("driveModeChooser", &driveModeChooser);
	SmartDashboard::PutString("DriveBase Current Command", this->GetCurrentCommandName());
	SmartDashboard::PutString("DriveBase Default Command", this->GetDefaultCommandName());
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

	SmartDashboard::PutString("Current Command", this->GetCurrentCommandName());
	SmartDashboard::PutNumber("Displacement", GetRelativeDisplacement());
	if (selectedDriveMode != driveModeChooser.GetSelected()->myDriveMode){
		SetDriveMode(driveModeChooser.GetSelected()->myDriveMode);
	}

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
		(new MyJoystickDrive())->Start();
		break;

	case Autonomous:
		turnController->Enable();
		driveController->Enable();
		(new CmdAuto_GyroDrive())->Start();
		break;
	}
}

void SubDriveBase::HandlePIDOutput(double xSpeed, double zRotation){
	//Run outputs from driveController and turnController
	bool isQuickTurn;
	if (xSpeed != 0){
		isQuickTurn = true;
	} else {
		isQuickTurn = false;
	}
	differentialDrive->CurvatureDrive(xSpeed, zRotation, isQuickTurn);
}

void SubDriveBase::Rotate(double angle){
	//Target a specific angle
	turnController->SetSetpoint(angle);
	turnController->Enable();
}

void SubDriveBase::GyroDrive(double distance){
	//Target a specific displacement
	SetEncodersToRelativeZero();
	driveController->SetSetpoint(distance);
	driveController->Enable();
}

bool SubDriveBase::ReachedTarget(){
	//Is the robot pointing at it's PID setpoint?
	return turnController->OnTarget();
}

void SubDriveBase::SetPIDSpeed(double speed){
	//This is a pretty hacked-together way of doing things,
	//BUT THERES ONLY FOUR DAYS LEFT! LEAVE ME ALONE!
	_Speed = speed;
}

void SubDriveBase::SetPIDRotation(double rotation){
	//Same as above
	_Rotation = rotation;
}

void SubDriveBase::ZeroNavX(){
	//Set NavX Gyro Yaw to zero
	navX->Reset();
}

double SubDriveBase::GetAngle(){
	return navX->GetAngle();
}

void SubDriveBase::SetEncodersToRelativeZero(){
	/*
	 * THIS DOES NOT ZERO THE ENCODERS!!
	 * It only remembers the current position and uses that as an effective zero when the
	 * GetRelativeDisplacement() function is called. for example, the robot might be
	 * in the middle of the field when this is called, setting relative zero to 5584.123,
	 * the robot then drives to position 6000, GetRelativeDisplacement() will then return
	 * 415.877 (= 6000-5584.123)
	 */
	relativeZero = sRXleft->GetSelectedSensorPosition(0);
}

double SubDriveBase::GetRelativeDisplacement(){
	//Return displacement relative to position where SetEncodersToRelativeZero() was called
	double relativeSensorUnits = (sRXleft->GetSelectedSensorPosition(0) - relativeZero);
	double relativeRotations = (relativeSensorUnits / 4096); //<-- Sensor units per rotation
	double relativeMeters = (relativeRotations * 0.319278); //<-- Circumference of wheels
	return relativeMeters;
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
