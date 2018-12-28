#include "Commands/CmdMakePath.h"
#include <iostream>

CmdMakePath::CmdMakePath() {
    // Use Requires() here to declare subsystem dependencies
    // eg. Requires(Robot::chassis.get());
    cout << "Running CmdMakePath::CmdMakePath()" << endl;
    pathFollower.reset(new PathFollower);
    cout << "Running CmdMakePath::Initialize()" << endl;
    path = pathFollower->constructVectorPath("test_left");
    int size = path.size();
    cout << "path of size " << size << " created." << endl;
    cout << "first points:" << endl; 
    for (int i = 0; i < min(size, 5); i++) {
        cout << "\t" << path[i].x << path[i].y << path[i].velocity << endl;
    }
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
