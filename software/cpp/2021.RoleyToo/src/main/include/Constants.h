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
  constexpr int spmDriveBaseFrontRight = 1;
  constexpr int spmDriveBaseBackRight = 2;
  constexpr int spmDriveBaseFrontLeft = 3;
  constexpr int spmDriveBaseBackLeft = 4;
  constexpr int spmFlywheelLeft = 5;
  constexpr int spmFlywheelRight = 6;
  constexpr int srxDolly = 7;
  constexpr int spmTurret = 8;
  constexpr int spmStorage = 9;
  constexpr int spmHood = 10;
  constexpr int spmClimbLeft = 11;
  constexpr int spmClimbRight = 12;
  constexpr int spmColorWheel = 13;
  constexpr int spmIntake = 14; 
  constexpr int spmFeeder = 15;
}

namespace dio {
  constexpr int hlfHoodDown = 0;
  constexpr int hlfTurretLeft = 1;
  constexpr int hlfTurretRight = 2;
  constexpr int lmtClimbStop = 5;
  constexpr int brkStorageIn = 7;
  constexpr int brkStorageIndex = 8;
  constexpr int brkStorageOut = 9;
  constexpr int lmtHoodBottom = 0;
}

namespace buttons {
  constexpr int aBtn = 1;
  constexpr int bBtn = 2;
  constexpr int xBtn = 3;
  constexpr int yBtn = 4; 
  constexpr int leftBtn = 5;
  constexpr int rightBtn = 6;
  constexpr int backBtn = 8; 
  constexpr int startBtn = 7; 
  constexpr int leftStickBtn = 9;
  constexpr int rightStickBtn = 10;

  constexpr int leftTrigger = 2;
  constexpr int rightTrigger = 3;
}

namespace pcm {
  constexpr int solDollyDeploy = 1;
  constexpr int pcm_solIntakeRetract = 2;
  constexpr int solClimbDeploy = 3;
  constexpr int solClimbRetract = 0; 
  constexpr int pcm_solIntakeDeploy = 6;
  constexpr int solDollyRetract = 7;
}