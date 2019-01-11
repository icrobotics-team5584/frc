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

    talIntakeOutakeRight.reset(new frc::Talon(can_talIntakeOutakeRight));
    talIntakeOutakeLeft.reset(new frc::Talon(can_talIntakeOutakeLeft));

}