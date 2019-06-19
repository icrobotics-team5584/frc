

#include "commands/CmdMoveArm.h"
#include "PidsrcArm.h"

CmdMoveArm::CmdMoveArm() {
}

void CmdMoveArm::Initialize()
{
	armController = new frc::PIDController(PIDp, PIDi, PIDd, _pidsrcArm, _armOutput);
	armController->SetInputRange(EncBack, EncFront);
	armController->SetOutputRange(-0.7, 0.7);
	armController->SetContinuous(false);
	frc::SmartDashboard::PutData("Arm PID Controls", armController);
}

// Called repeatedly when this Command is scheduled to run
void CmdMoveArm::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool CmdMoveArm::IsFinished()
{
  return false;
}
void CmdMoveArm::End() {}

void CmdMoveArm::Interrupted()
{
  End();
}

/*
PIDMag::~PIDMag() {
	// TODO Auto-generated destructor stub
}
*/
