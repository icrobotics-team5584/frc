#include "RobotMap.h"

RobotMap::RobotMap() {
    //Point DriveBase actuators to new objects
    srxDriveBaseLeft.reset(new WPI_TalonSRX(canID_srxDriveBaseFrontLeft));
    srxDriveBaseRight.reset(new WPI_TalonSRX(canID_srxDriveBaseFrontRight));
    srxDriveBaseLeftSlave.reset(new WPI_TalonSRX(canID_srxDriveBaseBackLeft));
    srxDriveBaseRightSlave.reset(new WPI_TalonSRX(canID_srxDriveBaseBackRight));

    // Point DriveBase sensors to new objects
    ahrsDriveBaseNavX.reset(new AHRS(SerialPort::kUSB)); //See navx-micro.kauailabs.com/guidance/selecting-an-interface.
        // for NavX micro: .reset(new AHRS(SerialPort::kUSB))
        // for NavX MXP  : .reset(new AHRS(SPI::Port::kMXP))

}