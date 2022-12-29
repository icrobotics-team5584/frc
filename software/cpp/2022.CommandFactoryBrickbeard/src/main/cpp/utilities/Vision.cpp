#include "utilities/Vision.h"
#include "subsystems/SubDrivebase.h"
#include "units/math.h"

namespace FakeVision {

units::meter_t GetDistToTarget() {
  auto robotPose = SubDrivebase::GetInstance().GetPose();
  return goalPosition.Distance(robotPose.Translation());
}

units::degree_t GetAngleToTarget() {
  auto robotPose = SubDrivebase::GetInstance().GetPose();
  frc::Pose2d robotToGoal = frc::Pose2d{goalPosition, 0_deg}.RelativeTo(robotPose);

  // angle = atan(opp/adj)
  return units::math::atan(robotToGoal.Y()/robotToGoal.X());
}

}  // namespace FakeVision