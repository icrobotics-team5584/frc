
#include "ctre/Phoenix.h"


#include "SubDriveBase.h"
#include "../RobotMap.h"
#include "Commands/MyJoystickDrive.h"

SubDriveBase::SubDriveBase() : frc::Subsystem("SubDriveBase") {
    sRXleft = RobotMap::subDriveBaseSRXleft;
    sRXright = RobotMap::subDriveBaseSRXright;
    myFirstDifferentialDrive = RobotMap::subDriveBaseMyFirstDifferentialDrive;

}

void SubDriveBase::InitDefaultCommand() {

        SetDefaultCommand(new MyJoystickDrive());

}

void SubDriveBase::Periodic() {

}


void SubDriveBase::TakeJoystickInputs(std::shared_ptr<Joystick> sticky ) {
	myFirstDifferentialDrive->ArcadeDrive(sticky->GetY(),sticky->GetX());
}

