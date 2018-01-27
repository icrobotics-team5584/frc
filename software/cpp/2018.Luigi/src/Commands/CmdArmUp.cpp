//#include "CmdArmUp.h"
//
//CmdArmUp::CmdArmUp() {
//	// Use Requires() here to declare subsystem dependencies
//	// eg. Requires(Robot::chassis.get());
//	Requires(Robot::subArmLift.get());
//}
//
//// Called just before this Command runs the first time
//void CmdArmUp::Initialize() {
//	Robot::subArmLift->Up();
//}
//
//// Called repeatedly when this Command is scheduled to run
//void CmdArmUp::Execute() {
//
//}
//
//// Make this return true when this Command no longer needs to run execute()
//bool CmdArmUp::IsFinished() {
//	if (Robot::subArmLift->GetTopSwitch()) {
//		return true;
//	} else {
//		return false;
//	}
//}
//
//
//// Called once after isFinished returns true
//void CmdArmUp::End() {
//	Robot::subArmLift->Stop();
//}
//
//// Called when another command which requires one or more of the same
//// subsystems is scheduled to run
//void CmdArmUp::Interrupted() {
//	End();
//}
