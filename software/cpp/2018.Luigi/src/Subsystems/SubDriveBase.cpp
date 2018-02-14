#include "SubDriveBase.h"
#include "Commands/MyJoystickDrive.h"
#include "Commands/CmdGyroTurn.h"

//PID turning constants
const static double p = 1;
const static double i = 0;
const static double d = 0;

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

    //setup NavX turning controller
    navX = RobotMap::navX.get();
    turnController = new PIDController(p, i, d, navX, this);
    turnController->SetInputRange(-180.0f, 180.0f);
    turnController->SetOutputRange(-1.0, 1.0);
    turnController->SetContinuous(true);
    turnController->SetAbsoluteTolerance(1);

	//Put NavX angle on Dashboard
	SmartDashboard::PutData("NavX", navX);
	SmartDashboard::PutData("turnController", turnController);
	driveModeChooser.AddDefault("Manual", new DriveModeClass(Manual));
	driveModeChooser.AddObject("Gyro", new DriveModeClass(Gyroscope));
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

	if (selectedDriveMode != driveModeChooser.GetSelected()->myDriveMode){
		SetDriveMode(driveModeChooser.GetSelected()->myDriveMode);
	}

}

void SubDriveBase::SetDriveMode(DriveMode driveMode){
	selectedDriveMode = driveMode;

	switch(driveMode){
	case Manual:
		turnController->Disable();
		SetCurrentCommand(new MyJoystickDrive());
		break;

	case Gyroscope:
		SetCurrentCommand(NULL);
		turnController->Enable();
		break;
	}
}

void SubDriveBase::Rotate(double angle){
	//Target a specific angle
	turnController->SetSetpoint(angle);
	turnController->Enable();
}

void SubDriveBase::PIDWrite(double rotation){
    // This function is invoked periodically by the PID Controller
	SmartDashboard::PutNumber("PIDWrite rotation", rotation);
	differentialDrive->CurvatureDrive(0, rotation, true);
}

bool SubDriveBase::ReachedTarget(){
	//Is the robot pointing at it's PID setpoint?
	return turnController->OnTarget();
}

void SubDriveBase::ZeroNavX(){
	//Set NavX Gyro Yaw to zero
	navX->Reset();
}

double SubDriveBase::GetAngle(){
	//Return current direction from NavX gyroscope
	return navX->GetAngle();
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
