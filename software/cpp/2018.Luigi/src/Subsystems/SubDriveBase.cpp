#include "SubDriveBase.h"
#include "Commands/MyJoystickDrive.h"

//PID turning constants
const static double p = 1;
const static double i = 0;
const static double d = 0;

SubDriveBase::SubDriveBase() : frc::Subsystem("SubDriveBase"), turnController(p, i, d, navX, this){
	//Drive wheels
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
    turnController.SetInputRange(-180.0f, 180.0f);
    turnController.SetOutputRange(-1.0, 1.0);
    turnController.SetAbsoluteTolerance(2);
    turnController.SetContinuous(true);
}

void SubDriveBase::InitDefaultCommand() {
	SetDefaultCommand(new MyJoystickDrive());
}

void SubDriveBase::Periodic() {

	//UltraSonic
	if (++_Ultraloops >= 30) {
		//frontUValue = ((((ultrasonicInputFront->GetValue())/ (5.0 / 500.0))/1000.0)+5.0);
		//rightUValue = ((((ultrasonicInputRight->GetValue())/ (5.0 / 500.0))/1000.0)+5.0);
		//backUValue = ((((ultrasonicInputBack->GetValue())/ (5.0 / 500.0))/1000.0)+5.0);
		//leftUValue = ((((ultrasonicInputLeft->GetValue())/ (5.0 / 500.0))/1000.0)+5.0);
		//frontUValue = ((ultrasonicInputFront->GetValue())/ 100000.0 );
		//frontUValue = ultrasonicInputFront->GetValue();

		//code for DIO echo ultrasonic sensors
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
		//frc::SmartDashboard::PutNumber("Ultra RAW, DIO:0", ultrasonicInputFront->GetValue());

		_Ultraloops = 0;
	}

	//Put NavX angle on Dashboard
	frc::SmartDashboard::PutData("NavX", navX);
}

void SubDriveBase::Rotate(double angle){
	//Target a specific angle, with a 2 deg tolerance (can be changed in constructor)
	turnController.SetSetpoint(angle);
}

void SubDriveBase::PIDWrite(double rotationSpeed){
    // This function is invoked periodically by the PID Controller
	this->AutoDrive(rotationSpeed, 0);
}

void SubDriveBase::ZeroNavX(){
	//Set NavX Gyro Yaw to zero
	navX->Reset();
}

void SubDriveBase::AutoDrive(double speed, double rotation) {
	//A basic drive with no sensor feedback
	differentialDrive->ArcadeDrive(speed, rotation);
}

void SubDriveBase::Stop(){
	//Stop the drive motors
	differentialDrive->ArcadeDrive(0,0);
}

void SubDriveBase::TakeJoystickInputs(std::shared_ptr<Joystick> sticky ) {
	//Drive with the Gamepad left stick, use L2 as boost
	double boost = (((sticky->GetRawAxis(2)+3))/4);
	differentialDrive->ArcadeDrive(-sticky->GetY() * boost, sticky->GetX() * boost);
}
