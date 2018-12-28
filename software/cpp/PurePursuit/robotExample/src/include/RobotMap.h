#pragma once

#include <WPILib.h>
#include <AHRS.h>
#include <ctre/Phoenix.h>

using namespace std;

/*
 * The RobotMap is a wiring map of all the components on the robot. It contains
 * the creation of all physical components present on the robot.
 * Ideally, if wiring changes on the robot, this is the only place that changes
 * need to be made.
 */

enum CanID {
    //DriveBase Actuator IDs
    canID_srxDriveBaseFrontLeft     = 8,
    canID_srxDriveBaseFrontRight    = 7,
    canID_srxDriveBaseBackLeft      = 6,
    canID_srxDriveBaseBackRight     = 5,
};

enum IOPort {
    //Sensors and stuff, example:
    ioPort_lidar        = 0,
    ioPort_autoChooser  = 1
};

class RobotMap {
public:
    RobotMap();

    // DriveBase Actuators
    shared_ptr<WPI_TalonSRX> srxDriveBaseLeft;
    shared_ptr<WPI_TalonSRX> srxDriveBaseRight;
    shared_ptr<WPI_TalonSRX> srxDriveBaseLeftSlave;
    shared_ptr<WPI_TalonSRX> srxDriveBaseRightSlave;

    // DriveBase Sensors
    shared_ptr<AHRS> ahrsDriveBaseNavX;
};

