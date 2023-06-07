// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/commands.h>

namespace cmd{
frc2::CommandPtr StartFlyWheel();
frc2::CommandPtr StopFlyWheel();
frc2::CommandPtr StartIndexer();
frc2::CommandPtr StopIndexer();
frc2::CommandPtr StopShooting();
frc2::CommandPtr StartShooting();
frc2::CommandPtr ShootBall();
}
