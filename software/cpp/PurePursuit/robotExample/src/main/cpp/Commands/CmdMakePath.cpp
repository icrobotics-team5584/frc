#include "Commands/CmdMakePath.h"
#include <iostream>
#include "Robot.h"

CmdMakePath::CmdMakePath() {
    // Use Requires() here to declare subsystem dependencies
    // eg. Requires(Robot::chassis.get());
    cout << "Running CmdMakePath::CmdMakePath()" << endl;
    posEncoderGyro.reset(new PosEncoderGyro);
    dvoTank.reset(new DriveOutput);
    pathFollower.reset(new PathFollower("test_left", posEncoderGyro, dvoTank));
}

// Called just before this Command runs the first time
void CmdMakePath::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void CmdMakePath::Execute() {

    pathFollower->followPath();

    pair<double, double> currentPosition = posEncoderGyro->get();

    SmartDashboard::PutNumber("angle", Robot::subDriveBase->getAngle());
    SmartDashboard::PutNumber("dist", Robot::subDriveBase->getDistance());
    SmartDashboard::PutNumber("x pos", currentPosition.first);
    SmartDashboard::PutNumber("y pos", currentPosition.second);
}

// Make this return true when this Command no longer needs to run execute()
bool CmdMakePath::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdMakePath::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdMakePath::Interrupted() {}
