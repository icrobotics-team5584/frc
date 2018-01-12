#include "SubDriveBase.h"
#include <wpilib.h>
#include "Commands/CmdJoystickDrvie.h"

SubDriveBase::SubDriveBase() : Subsystem("ExampleSubsystem") {

	tnxLeftDriveMaster.reset(new WPI_TalonSRX(1));
    tnxLeftDriveSlave.reset(new WPI_TalonSRX(2));
    tnxRightDriveMaster.reset(new WPI_TalonSRX(3));
    tnxRightDriveSlave.reset(new WPI_TalonSRX(4));

    differentialDrive.reset(new DifferentialDrive(*tnxLeftDriveMaster, *tnxRightDriveMaster) );
    differentialDrive->SetSafetyEnabled(true);
	differentialDrive->SetExpiration(0.1);
	differentialDrive->SetMaxOutput(1.0);
}

void SubDriveBase::InitDefaultCommand() {
	SetDefaultCommand(new CmdPnuematicOutputOut());
}

void SubDriveBase::TakeJoystickInputs(std::shared_ptr<Joystick> stick) {
	differentialDrive->ArcadeDrive(stick->GetX(), stick->GetY());
}

void SubDriveBase::Drive(double power, double direction) {

}

void SubDriveBase::Stop() {

}
