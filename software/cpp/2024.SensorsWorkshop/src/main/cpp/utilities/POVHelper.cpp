#include "utilities/POVHelper.h"
#include <frc2/command/CommandScheduler.h>

namespace POVHelper
{
    frc2::Trigger Up(frc2::CommandXboxController* controller) {
      return frc2::Trigger(
          frc2::CommandScheduler::GetInstance().GetDefaultButtonLoop(),
          [=] { return controller->GetPOV() == 0; });
    }

    frc2::Trigger Down(frc2::CommandXboxController* controller) {
      return frc2::Trigger(
          frc2::CommandScheduler::GetInstance().GetDefaultButtonLoop(),
          [=] { return controller->GetPOV() == 180; });
    }

    frc2::Trigger Left(frc2::CommandXboxController* controller) {
      return frc2::Trigger(
          frc2::CommandScheduler::GetInstance().GetDefaultButtonLoop(),
          [=] { return controller->GetPOV() == 270; });
    }

    frc2::Trigger Right(frc2::CommandXboxController* controller) {
      return frc2::Trigger(
          frc2::CommandScheduler::GetInstance().GetDefaultButtonLoop(),
          [=] { return controller->GetPOV() == 90; });
    }
} // namespace POVHelper
