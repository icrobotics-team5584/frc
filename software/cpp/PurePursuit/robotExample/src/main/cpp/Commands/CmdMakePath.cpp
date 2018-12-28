#include "Commands/CmdMakePath.h"
#include <iostream>

CmdMakePath::CmdMakePath() {
    // Use Requires() here to declare subsystem dependencies
    // eg. Requires(Robot::chassis.get());
    pathFollower.reset(new PathFollower("test_left", posEncoderGyro.get(), dvoTank.get()));
}

// Called just before this Command runs the first time
void CmdMakePath::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void CmdMakePath::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool CmdMakePath::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdMakePath::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdMakePath::Interrupted() {}
