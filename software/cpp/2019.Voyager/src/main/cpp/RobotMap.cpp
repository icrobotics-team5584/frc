#include "RobotMap.h"
#include <iostream>
RobotMap::RobotMap(){
    cout << "Run robot map" << endl;
    srxDriveBaseFrontRight.reset(new WPI_TalonSRX(can_srxDriveBaseFrontRight));
    srxDriveBaseFrontLeft.reset(new WPI_TalonSRX(can_srxDriveBaseFrontLeft));
    srxDriveBaseBackLeft.reset(new WPI_TalonSRX(can_srxDriveBaseBackLeft));
    srxDriveBaseBackRight.reset(new WPI_TalonSRX(can_srxDriveBaseBackRight));
    srxDriveBaseBackRight->Set(ControlMode::Follower, can_srxDriveBaseFrontRight);
    srxDriveBaseBackLeft->Set(ControlMode::Follower, can_srxDriveBaseFrontLeft);

    //Create drivebase sensors
    //ulsDriveBaseLeft.reset(new Ultrasonic(0, 1, Ultrasonic::kMilliMeters));
    ulsTriggerDriveBaseLeft.reset(new DigitalOutput(0));
    ulsEchoDriveBaseLeft.reset(new DigitalInput(1));
    ulsDriveBaseLeft.reset(new Ultrasonic(ulsTriggerDriveBaseLeft, ulsEchoDriveBaseLeft));
    ahrsDriveBaseNavXGyro.reset(new AHRS(SerialPort::kMXP));
    clsDriveBaseLeft.reset(new DigitalInput(2));
}