#include "SubDriveBase.h"
#include "Commands/MyJoystickDrive.h"


SubDriveBase::SubDriveBase() : frc::Subsystem("SubDriveBase") {
    sRXleft = RobotMap::subDriveBaseSRXleft;
    sRXright = RobotMap::subDriveBaseSRXright;
    differentialDrive = RobotMap::subDriveBaseDifferentialDrive;

    ultrasonicInputFront = RobotMap::subDriveBaseUltrasonicInputFront;
    ultrasonicInputRight = RobotMap::subDriveBaseUltrasonicInputRight;
    ultrasonicInputBack = RobotMap::subDriveBaseUltrasonicInputBack;
    ultrasonicInputLeft = RobotMap::subDriveBaseUltrasonicInputLeft;
}

void SubDriveBase::InitDefaultCommand() {
	SetDefaultCommand(new MyJoystickDrive());
}

void SubDriveBase::Periodic() {

//	frontUValue = ((((ultrasonicInputFront->GetValue())/ (5.0 / 500.0))/1000.0)+5.0);
//	rightUValue = ((((ultrasonicInputFront->GetValue())/ (5.0 / 500.0))/1000.0)+5.0);
//	backUValue = ((((ultrasonicInputFront->GetValue())/ (5.0 / 500.0))/1000.0)+5.0);
//	leftUValue = ((((ultrasonicInputFront->GetValue())/ (5.0 / 500.0))/1000.0)+5.0);
//	//frontUValue = ((ultrasonicInputFront->GetValue())/ 100000.0 );
//	//frontUValue = ultrasonicInputFront->GetValue();
//
//
//	frc::SmartDashboard::PutNumber("Ultra, front, DIO:0", frontUValue);
//	frc::SmartDashboard::PutNumber("Ultra, right, DIO:0", rightUValue);
//	frc::SmartDashboard::PutNumber("Ultra, back, DIO:0", backUValue);
//	frc::SmartDashboard::PutNumber("Ultra, left, DIO:0", leftUValue);
//	//frc::SmartDashboard::PutNumber("Ultra RAW, DIO:0", ultrasonicInputFront->GetValue());

}

void SubDriveBase::AutoDrive(double speed, double rotation) {
	differentialDrive->ArcadeDrive(speed, rotation);
}

void SubDriveBase::Stop(){
	differentialDrive->ArcadeDrive(0,0);
}

void SubDriveBase::TakeJoystickInputs(std::shared_ptr<Joystick> sticky ) {
	double throttle = (((sticky->GetRawAxis(3) + 1 ) / 4 )*-1 ) +1;
	differentialDrive->ArcadeDrive(-sticky->GetY() * throttle, sticky->GetX() * throttle);
}
