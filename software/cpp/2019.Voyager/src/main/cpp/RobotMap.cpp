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
    ulsDriveBaseLeft.reset(new AnalogInput(0));
    ahrsDriveBaseNavXGyro.reset(new AHRS(SerialPort::kMXP));
    clsDriveBaseLeft.reset(new DigitalInput(0));
    
}