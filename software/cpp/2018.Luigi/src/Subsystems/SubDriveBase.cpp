#include "SubDriveBase.h"

SubDriveBase::SubDriveBase() : Subsystem("ExampleSubsystem") {

	tnxLeftDriveMaster.reset(new WPI_TalonSRX(1));
    tnxLeftDriveSlave.reset(new WPI_TalonSRX(2));
    tnxRightDriveMaster.reset(new WPI_TalonSRX(3));
    tnxRightDriveSlave.reset(new WPI_TalonSRX(4));

    differentialDrive.reset(new DifferentialDrive(*tnxLeftDriveMaster, *tnxRightDriveMaster) );
}

void SubDriveBase::InitDefaultCommand() {

}

void SubDriveBase::TakeJoystickInputs(std::shared_ptr<Joystick> stick) {
	differentialDrive->ArcadeDrive(stick->GetX(), stick->GetY());
}

void SubDriveBase::Drive(double power, double direction) {

}

void SubDriveBase::Stop() {

}
