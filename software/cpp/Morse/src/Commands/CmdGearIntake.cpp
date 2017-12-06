#include "CmdGearIntake.h"

CmdGearIntake::CmdGearIntake() {
	Requires(Robot::subGearPickup.get());
}

// Called just before this Command runs the first time
void CmdGearIntake::Initialize() {
	Robot::subGearPickup->Out();
	Robot::subGearPickup->Suck();
}

// Called repeatedly when this Command is scheduled to run
void CmdGearIntake::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool CmdGearIntake::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CmdGearIntake::End() {
	Robot::subGearPickup->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdGearIntake::Interrupted() {
	End();
}
