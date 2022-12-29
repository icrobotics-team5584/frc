#pragma once

#include <frc2/command/commands.h>

namespace cmd {
    frc2::CommandPtr RunStorage();
    frc2::CommandPtr Intake(); 
    frc2::CommandPtr Shoot(); 
    frc2::CommandPtr AimAndShootTwice(); 
    frc2::CommandPtr AccelerateFlyweelToTarget();
}