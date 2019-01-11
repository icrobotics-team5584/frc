/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include <ctre/Phoenix.h>
#include <frc/WPILib.h>

using namespace std;
using namespace frc;

enum Can {
    can_srxDriveBaseFrontRight = 1,
    can_srxDriveBaseFrontLeft = 3,
    can_srxDriveBaseBackRight = 2,
    can_srxDriveBaseBackLeft = 4
};

enum DIO {
    dio_clsDriveBaseFront = 0,
    dio_ulsTriggerDriveBaseLeft = 1,
    dio_ulsEchoDriveBaseLeft = 2,
    dio_ulsTriggerDriveBaseRight = 3,
    dio_ulsEchoDriveBaseRight = 4,
};

enum Analog {
    ana_clsDriveBaseMid = 0,
};

enum PCM {
    pcm_solPanelAffectorTopLeftForward = 0,
    pcm_solPanelAffectorTopLeftReverse = 1,
    pcm_solPanelAffectorTopRightForward = 2,
    pcm_solPanelAffectorTopRightReverse = 3,
    pcm_solPanelAffectorBottomLeftForward = 4,
    pcm_solPanelAffectorBottomLeftReverse = 5,
    pcm_solPanelAffectorBottomRightForward = 6,
    pcm_solPanelAffectorBottomRightReverse = 7,
};

class RobotMap {
public:
    RobotMap();

    // DriveBase Actuators
    shared_ptr<WPI_TalonSRX> srxDriveBaseFrontRight;
	shared_ptr<WPI_TalonSRX> srxDriveBaseFrontLeft;
    shared_ptr<WPI_TalonSRX> srxDriveBaseBackLeft;
	shared_ptr<WPI_TalonSRX> srxDriveBaseBackRight;

    // DriveBase Sensors
    shared_ptr<AnalogInput> clsDriveBaseMid;
    shared_ptr<DigitalInput> clsDriveBaseFront;
    shared_ptr<Ultrasonic> ulsDriveBaseLeft;
    shared_ptr<Ultrasonic> ulsDriveBaseRight;

    // Panel Affector Actuators
    shared_ptr<DoubleSolenoid> solPanelAffectorTopLeft;
    shared_ptr<DoubleSolenoid> solPanelAffectorTopRight;
    shared_ptr<DoubleSolenoid> solPanelAffectorBottomLeft;
    shared_ptr<DoubleSolenoid> solPanelAffectorBottomRight;

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
