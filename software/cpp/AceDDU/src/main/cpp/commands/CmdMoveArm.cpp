

#include "commands/CmdMoveArm.h"
#include "PidsrcArm.h"

PIDMag::PIDMag() {
	armController = new frc::PIDController(PIDp, PIDi, PIDd, _pidsrcArm, _armOutput);
	armController->SetInputRange(EncBack, EncFront);
	armController->SetOutputRange(-0.7, 0.7);
	armController->SetContinuous(false);

	frc::SmartDashboard::PutData("Arm PID Controls", armController);
}
/*
PIDMag::~PIDMag() {
	// TODO Auto-generated destructor stub
}
*/
