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

namespace DriveConstants{
    constexpr int driveLeftFront = 1;
    constexpr int driveLeftBack = 2;
    constexpr int driveRightFront = 3;
    constexpr int driveRightBack = 4;
}

namespace TurretConstants {
    constexpr int turretEncoderPin1 = 0;
    constexpr int turretEncoderPin2 = 1;
    constexpr int turretMotor = 8;
    constexpr int turretLimit = 9;
    constexpr int turretLinebreak = 8;

    constexpr int flywheelMotor = 5;
}

namespace ContainerConstants {
    constexpr int kDriverControllerPort = 0;
}

namespace TestConstants {
    constexpr int testMotor1 = 5;
    constexpr int testMotor2 = 6;
    constexpr int testMotor3 = 7;
}

namespace Buttons {
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

namespace POVPositions {
      constexpr int UP = 0;
      constexpr int UP_RIGHT = 45;
      constexpr int RIGHT = 90;
      constexpr int DOWN_RIGHT = 135;
      constexpr int DOWN = 180;
      constexpr int DOWN_LEFT = 225;
      constexpr int LEFT = 270;
      constexpr int UP_LEFT = 315;
}

namespace Triggers {
      constexpr int triggerL = 2;
      constexpr int triggerR = 3;
}