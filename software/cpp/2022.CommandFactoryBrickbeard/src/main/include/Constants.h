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
  constexpr int frontLeftDrive = 1;
  constexpr int backLeftDrive = 2;
  constexpr int frontRightDrive = 3;
  constexpr int backRightDrive = 4;
  constexpr int shooterA = 5;
  constexpr int shooterB = 6;
  constexpr int intake = 7;
  constexpr int storage = 8;
  constexpr int climberLeft = 9;
  constexpr int climberRight = 10;
}  // namespace canid

namespace pcm {
  constexpr int intakeForward = 0;
  constexpr int intakeReverse = 1;
  constexpr int storageStopperForward = 2;
  constexpr int storageStopperReverse = 3;
  constexpr int climberTilterForward = 4;
  constexpr int climberTilterReverse = 5;
}  // namespace pcm

namespace dio {
  constexpr int climberLeftUpperLimit = 0;
  constexpr int climberRightUpperLimit = 1;
  constexpr int climberLeftLowerLimit = 2;
  constexpr int climberRightLowerLimit = 3;
}