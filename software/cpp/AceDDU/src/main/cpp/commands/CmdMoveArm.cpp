

#include "commands/CmdMoveArm.h"
#include "PidsrcArm.h"
#include <iostream>

CmdMoveArm::CmdMoveArm() {
  std::cout << "Arm Constructor Started" << std::endl;
}

void CmdMoveArm::Initialize()
{
  std::cout << "CmdArmInit" << std::endl;
	armController = new frc::PIDController(PIDp, PIDi, PIDd, _pidsrcArm, _armOutput);
	armController->SetInputRange(EncBack, EncFront);
	armController->SetOutputRange(-0.7, 0.7);
	armController->SetContinuous(false);
	frc::SmartDashboard::PutData("Arm PID Controls", armController);
	armController->Enable();
  std::cout << "CmdArmInit Done" << std::endl;
}

// Called repeatedly when this Command is scheduled to run
void CmdMoveArm::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool CmdMoveArm::IsFinished()
{
  if (armController->OnTarget())
  {
    return true;
  }

  else
  {
    return false;
  }
  std::cout << "isFinished" << std::endl;
}
void CmdMoveArm::End() {
	armController->Disable();
  std::cout << "End" << std::endl;
}

void CmdMoveArm::Interrupted()
{
  End();
}

/*
PIDMag::~PIDMag() {
	// TODO Auto-generated destructor stub
}
*/
