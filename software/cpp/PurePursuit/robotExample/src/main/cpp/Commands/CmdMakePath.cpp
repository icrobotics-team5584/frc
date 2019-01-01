#include "Commands/CmdMakePath.h"
#include <iostream>
#include "Robot.h"

CmdMakePath::CmdMakePath() {
    cout << "Start of CmdMakePath()" << endl;

    // Use Requires() here to declare subsystem dependencies
    Requires(Robot::subDriveBase.get());
    cout << "Running CmdMakePath::CmdMakePath()" << endl;
    posEncoderGyro.reset(new PosEncoderGyro);
    dvoTank.reset(new DvoTank);
    pathFollower.reset(new PathFollower("test_left", posEncoderGyro, dvoTank));

    cout << "End of CmdMakePath()" << endl;
}

// Called just before this Command runs the first time
void CmdMakePath::Initialize() {
    pathFollower->reset();
}
// Called repeatedly when this Command is scheduled to run
void CmdMakePath::Execute() {
    pathFollower->followPath();
}

// Make this return true when this Command no longer needs to run execute()
bool CmdMakePath::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdMakePath::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdMakePath::Interrupted() {}
