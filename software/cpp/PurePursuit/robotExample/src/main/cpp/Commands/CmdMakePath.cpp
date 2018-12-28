#include "Commands/CmdMakePath.h"
#include "purePursuit/include/pathFollower.hpp"
#include <iostream>

CmdMakePath::CmdMakePath() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  cout << "Constructing a CmdMakePath" << endl;
  PathFollower pf;
  path = pf.constructVectorPath("test_left");
  cout << "Finished constructVectorPath" << endl;
}

// Called just before this Command runs the first time
void CmdMakePath::Initialize() {
  cout << "Running CmdMakePath::Initialize()" << endl;
  cout << "path size: " << path.size() << endl;

  for (int i=0; i<path.size(); i++) {
    cout << "point " << i << ": ";
    cout << path[i].x << path[i].y << path[i].velocity << endl;
  }
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
