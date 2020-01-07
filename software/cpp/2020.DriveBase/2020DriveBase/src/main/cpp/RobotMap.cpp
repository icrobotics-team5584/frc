/*

*/

#include <RobotMap.h>

RobotMap::RobotMap() {
    srxDriveBaseFrontLeft.reset(new TalonSRX(can_srxDriveBaseFrontLeft));
    srxDriveBaseBackLeft.reset(new TalonSRX(can_srxDriveBaseBackLeft));
    srxDriveBaseFrontRight.reset(new TalonSRX(can_srxDriveBaseFrontRight));
    srxDriveBaseBackRight.reset(new TalonSRX(can_srxDriveBaseBackRight));

}