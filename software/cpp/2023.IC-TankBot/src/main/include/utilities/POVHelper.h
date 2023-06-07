#pragma once

#include <frc2/command/button/Trigger.h>
#include <frc2/command/button/CommandXboxController.h>

namespace POVHelper {
  frc2::Trigger Up(frc2::CommandXboxController* controller);
  frc2::Trigger Down(frc2::CommandXboxController* controller);
  frc2::Trigger Left(frc2::CommandXboxController* controller);
  frc2::Trigger Right(frc2::CommandXboxController* controller);
};
