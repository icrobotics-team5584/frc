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
    constexpr int spmDriveBaseFrontLeft = 1;
    constexpr int spmDriveBaseBackLeft = 2;
    constexpr int spmDriveBaseFrontRight = 3;
    constexpr int spmDriveBaseBackRight = 4;
    constexpr int spmFlywheelRight = 5;
    constexpr int spmFlywheelLeft = 6;
    constexpr int srxDolly = 7;
    constexpr int spmTurret = 8;
    constexpr int spmStorage = 9;
    constexpr int spmHood = 10;
}
namespace dio {
    constexpr int encTurret1 = 0;
    constexpr int encTurret2 = 1;
    constexpr int hlfTurretLeft = 2;
    constexpr int hlfTurretRight = 3;
    constexpr int encHood1 = 4;
    constexpr int encHood2 = 5;
    constexpr int hlfHoodDown = 6;
}
namespace buttons {
    constexpr int aBtn = 1;
    constexpr int bBtn = 2;
    constexpr int xBtn = 3;
    constexpr int yBtn = 4; 
    constexpr int leftBtn = 5;
    constexpr int rightBtn = 6;
    constexpr int backBtn = 7; 
    constexpr int startBtn = 8; 
    constexpr int leftStickBtn = 9;
    constexpr int rightStickBtn = 10;
}
namespace pcm {
    constexpr int solDollyDeploy = 2;
    constexpr int solDollyRetract = 3;
}