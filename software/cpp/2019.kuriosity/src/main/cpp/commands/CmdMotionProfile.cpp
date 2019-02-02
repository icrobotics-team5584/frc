#include "commands/CmdMotionProfile.h"
#include "Robot.h"
#include <pathfinder.h>

CmdMotionProfile::CmdMotionProfile() {
  // Use Requires() here to declare subsystem dependencies
  Requires(Robot::subDriveBase.get());
  mpData.reset(new MotionProfileData());

}

// Called just before this Command runs the first time
void CmdMotionProfile::Initialize() {
  Segment *segment = Robot::subDriveBase->generatePath();
  int pathLength = Robot::subDriveBase->getPathLength();
  double wheelBaseWidth = Robot::subDriveBase->WHEEL_BASE_WIDTH; 
  mpData->ReadMotionProfile(segment, pathLength, wheelBaseWidth);
  std::shared_ptr<WPI_TalonSRX> srxLeft = Robot::_robotMap->srxDriveBaseFrontLeft;
  std::shared_ptr<WPI_TalonSRX> srxRight = Robot::_robotMap->srxDriveBaseFrontRight;
  mpControl.reset(new MotionProfileControl(srxLeft, srxRight, mpData, 10));
  mpControl->initialise();
  delete segment;
}

// Called repeatedly when this Command is scheduled to run
void CmdMotionProfile::Execute() {
	mpControl->execute();
}

// Make this return true when this Command no longer needs to run execute()
bool CmdMotionProfile::IsFinished() { 
  bool finished = !mpControl->IsRunning();
  return finished; 
}

// Called once after isFinished returns true
void CmdMotionProfile::End() {
  mpControl->stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdMotionProfile::Interrupted() {
  End();
}
