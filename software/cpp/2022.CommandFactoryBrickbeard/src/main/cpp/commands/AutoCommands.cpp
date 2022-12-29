#include "commands/AutoCommands.h"
#include "commands/BallCommands.h"
#include "subsystems/SubDrivebase.h"
#include <pathplanner/lib/PathPlanner.h>
#include <pathplanner/lib/auto/RamseteAutoBuilder.h>
#include <unordered_map>

namespace cmd {

using namespace pathplanner;
using namespace frc2::cmd;

frc2::CommandPtr PPDrivePath() {
  // Load path as path group (paths split by the stop events created in the path planner UI)
  auto pathGroup = PathPlanner::loadPathGroup("4ball", {{4_mps, 3_mps_sq}, {4_mps, 3_mps_sq}});

  // Display paths on dashboard (the field display is managed by SubDrivebase)
  int pathNum = 0;
  for (auto path : pathGroup) {
    std::string pathName = fmt::format("auto path {}", pathNum);
    auto trajectory = path.asWPILibTrajectory();
    SubDrivebase::GetInstance().DisplayTrajectory(pathName, trajectory);
    pathNum++;
  }

  // Map the event names used in PathPlanner markers to commands
  std::unordered_map<std::string, std::shared_ptr<frc2::Command>> eventMap{
      {"AimAndShootTwice", AimAndShootTwice().Unwrap()},
      {"Intake3Sec", Intake().WithTimeout(3_s).Unwrap()},
      {"AccelerateFlyweelToTarget", AccelerateFlyweelToTarget().Unwrap()}};

  // Create an object that has all the info and functions needed to follow an auto path.
  // Path Planner calls this an AutoBuilder, the Ramsete one is for tank drives, there are also
  // AutoBulders for swerve and mecanum drives
  static RamseteAutoBuilder autoBuilder{
    [] { return SubDrivebase::GetInstance().GetPose(); },
    [](frc::Pose2d pose) { SubDrivebase::GetInstance().SetPose(pose); },
    SubDrivebase::GetInstance().GetController(),
    SubDrivebase::GetInstance().GetKinematics(),
    [](units::meters_per_second_t left, units::meters_per_second_t right) {
      SubDrivebase::GetInstance().DriveSpeeds(left, right);
    },
    eventMap,
    {&SubDrivebase::GetInstance()} // Add drivebase as cmd requirement
  };

  // Create a command that follows the path group and executes commands from the eventMap along 
  // the way.
  return autoBuilder.fullAuto(pathGroup);
}

}  // namespace cmd
