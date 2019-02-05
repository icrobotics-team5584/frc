#include "RobotMap.h"

RobotMap::RobotMap() {
    // Point DriveBase actuators to new objects
    srxDriveBaseLeft.reset(new WPI_TalonSRX(canID_srxDriveBaseFrontLeft));
    srxDriveBaseRight.reset(new WPI_TalonSRX(canID_srxDriveBaseFrontRight));
    srxDriveBaseLeftSlave.reset(new WPI_TalonSRX(canID_srxDriveBaseBackLeft));
    srxDriveBaseRightSlave.reset(new WPI_TalonSRX(canID_srxDriveBaseBackRight));

    // Set slaves to follow front DriveBase motors
    srxDriveBaseLeftSlave->Set(ControlMode::Follower, canID_srxDriveBaseFrontLeft);
    srxDriveBaseRightSlave->Set(ControlMode::Follower, canID_srxDriveBaseFrontRight);

    // Select encoder types on drive motors
    srxDriveBaseLeft->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 20);
    srxDriveBaseRight->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, 20);

    // Point DriveBase sensors to new objects
    ahrsDriveBaseNavX.reset(new AHRS(SPI::Port::kMXP)); //See navx-micro.kauailabs.com/guidance/selecting-an-interface.
        // for NavX micro: .reset(new AHRS(SerialPort::kUSB))
        // for NavX MXP  : .reset(new AHRS(SPI::Port::kMXP))

}