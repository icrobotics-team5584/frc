// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

/**
 * The Constants header provides a convenient place for teams to hold robot-wide
 * numerical or boolean constants.  This should not be used for any other
 * purpose.
 *
 * It is generally a good idea to place constants into subsystem- or
 * command-specific namespaces within this header, which can then be used where
 * they are needed.
 */

namespace canid {

constexpr int LeftDriveMain = 1;
constexpr int LeftDriveFollower = 3;
constexpr int RightDriveMain = 2;
constexpr int RightDriveFollower = 4;
constexpr int IndexerMotor = 14;
constexpr int FlyWheelMotor = 12;
}  // namespace OperatorConstants
