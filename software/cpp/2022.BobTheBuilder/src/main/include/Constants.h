// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <frc/kinematics/DifferentialDriveKinematics.h>
#include <frc/trajectory/constraint/DifferentialDriveKinematicsConstraint.h>
#include <units/acceleration.h>
#include <units/angle.h>
#include <units/length.h>
#include <units/time.h>
#include <units/velocity.h>
#include <units/voltage.h>
#include <wpi/numbers>

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

namespace can {
  constexpr int spmDriveBaseFrontRight = 3;
  constexpr int spmDriveBaseBackRight = 1;
  constexpr int spmDriveBaseFrontLeft = 4;
  constexpr int spmDriveBaseBackLeft = 2;
}

constexpr auto kTrackwidth = 0.62_m;
const frc::DifferentialDriveKinematics kDriveKinematics(kTrackwidth);

namespace DriveConstants{
  // These are example values only - DO NOT USE THESE FOR YOUR OWN ROBOT!
  // These characterization values MUST be determined either experimentally or
  // theoretically for *your* robot's drive. The Robot Characterization
  // Toolsuite provides a convenient tool for obtaining these values for your
  // robot.
  constexpr auto ks = 0.12889_V;
  constexpr auto kv = 0.021317_V * 6.98_s / 1_m;
  constexpr auto ka = 0.0046239_V * 6.98_s * 6.98_s / 1_m;

  // Example value only - as above, this must be tuned for your drive!
  constexpr double kPDriveVel = 0.029512;
}

namespace AutoConstants {
constexpr auto kMaxSpeed = 3_mps;
constexpr auto kMaxAcceleration = 3_mps_sq;

// Reasonable baseline values for a RAMSETE follower in units of meters and
// seconds
constexpr auto kRamseteB = 2.0 * 1_rad * 1_rad / (1_m * 1_m);
constexpr auto kRamseteZeta = 0.7 / 1_rad;
}  // namespace AutoConstants

constexpr double kEncoderCPR = 1;
constexpr double kWheelDiameterMetres = 0.15; 
constexpr double kEncoderDistancePerPulse = (kWheelDiameterMetres * wpi::numbers::pi)/ kEncoderCPR / 8.45;
constexpr double kEncoderVelocityPerPulse = (kWheelDiameterMetres * wpi::numbers::pi)/ kEncoderCPR / 8.45 / 42;
