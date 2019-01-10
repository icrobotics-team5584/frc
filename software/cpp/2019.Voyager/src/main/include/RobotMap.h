/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include <ctre/Phoenix.h>
#include <WPILib.h>
#include <AHRS.h>

using namespace std;

enum Can {
    can_srxDriveBaseFrontRight = 1,
    can_srxDriveBaseFrontLeft = 3,
    can_srxDriveBaseBackRight = 2,
    can_srxDriveBaseBackLeft = 4,
};

class RobotMap {
public:
    shared_ptr<WPI_TalonSRX> srxDriveBaseFrontRight;
	shared_ptr<WPI_TalonSRX> srxDriveBaseFrontLeft;
    shared_ptr<WPI_TalonSRX> srxDriveBaseBackLeft;
	shared_ptr<WPI_TalonSRX> srxDriveBaseBackRight;

    shared_ptr<DigitalOutput> ulsTriggerDriveBaseLeft;
    shared_ptr<DigitalInput> ulsEchoDriveBaseLeft;
    shared_ptr<Ultrasonic> ulsDriveBaseLeft;
    shared_ptr<AHRS> ahrsDriveBaseNavXGyro;
    shared_ptr<DigitalInput> clsDriveBaseLeft;
    RobotMap();

};

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */

// For example to map the left and right motors, you could define the
// following variables to use with your drivetrain subsystem.
// constexpr int kLeftMotor = 1;
// constexpr int kRightMotor = 2;

// If you are using multiple modules, make sure to define both the port
// number and the module. For example you with a rangefinder:
// constexpr int kRangeFinderPort = 1;
// constexpr int kRangeFinderModule = 1;
