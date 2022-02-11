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
  constexpr int spmDolly = 5;
  constexpr int spmIntake = 7;
  constexpr int spmShooter1 = 8;
  constexpr int spmShooter2 = 12;
}

namespace pcm {
  constexpr int solDollyDeploy = 0;
  constexpr int solDollyRetract = 1;
  constexpr int solIntakeOut = 4;
  constexpr int solIntakeIn = 5;
}
