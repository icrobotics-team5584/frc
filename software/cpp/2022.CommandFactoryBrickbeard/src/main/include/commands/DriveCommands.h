#pragma once

#include <frc2/command/commands.h>
#include <frc2/command/button/CommandXboxController.h>

namespace cmd {
    frc2::CommandPtr JoystickDrive(frc2::CommandXboxController& controller);
    frc2::CommandPtr AimAtTarget();
}