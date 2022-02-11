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

namespace can {
  constexpr int spmDriveBaseFrontRight = 3;
  constexpr int spmDriveBaseBackRight = 1;
  constexpr int spmDriveBaseFrontLeft = 4;
  constexpr int spmDriveBaseBackLeft = 2;
  constexpr int spmStorage = 11;
  constexpr int spmDolly = 5;
}

namespace pcm {
  constexpr int solDollyDeploy = 3;
  constexpr int solDollyRetract = 2;
  constexpr int spmShooter1 = 5;
  constexpr int spmShooter2 = 6;
  constexpr int spmIntake = 7;
}
