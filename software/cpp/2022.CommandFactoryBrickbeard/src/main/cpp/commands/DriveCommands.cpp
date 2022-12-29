#include "commands/DriveCommands.h"
#include "subsystems/SubDrivebase.h"
#include "utilities/Vision.h"

namespace cmd {
using namespace frc2::cmd;

/*
 * Drive with inputs from an XboxController
 * Requires: SubDrivebase
 */
frc2::CommandPtr JoystickDrive(frc2::CommandXboxController& controller) {
  return Run(
    // Put a & in the [] (aka lambda capture) so the lamda has access to outer variables,
    // we particularly want it to have access to controller.
    [&] { 
      SubDrivebase::GetInstance().Drive(-controller.GetLeftY(), -controller.GetLeftX());
    }, 
    {&SubDrivebase::GetInstance()}
  );
}

/*
 * Aim the drivebase toward the vision target.
 * Requires: SubDrivebase
 */
frc2::CommandPtr AimAtTarget() {
  return Run(
    [] {
      SubDrivebase::GetInstance().RotateTowardZero(FakeVision::GetAngleToTarget());
    }, 
    {&SubDrivebase::GetInstance()}
  );
}

}  // namespace cmd