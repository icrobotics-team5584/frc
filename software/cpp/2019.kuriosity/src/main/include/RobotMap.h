/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include <ctre/Phoenix.h>
#include <AHRS.h>
#include <frc/WPILib.h>

using namespace std;
using namespace frc;

enum Can {
    can_srxDriveBaseFrontRight = 1,
    can_srxDriveBaseFrontLeft = 3,
    can_srxDriveBaseBackRight = 2,
    can_srxDriveBaseBackLeft = 4
};

enum PWM {
    pwm_talIntakeOutakeRight = 1, 
    pwm_talIntakeOutakeLeft = 0,   
    pwm_spkRollerIntake = 2
};

enum DIO {
    dio_clsDriveBaseFront = 0,
    dio_clsDriveBaseMid = 1,
    dio_ulsTriggerDriveBaseLeft = 2,
    dio_ulsEchoDriveBaseLeft = 3,
    dio_ulsTriggerDriveBaseRight = 4,
    dio_ulsEchoDriveBaseRight = 5,
};

enum Analog {
};

enum PCM {
    pcm_solPanelAffectorTopForward = 3,
    pcm_solPanelAffectorTopReverse = 2,
    pcm_solPanelAffectorBottomForward = 1,
    pcm_solPanelAffectorBottomReverse = 0
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
    shared_ptr<AHRS> ahrsNavXDriveBase;
    shared_ptr<DigitalInput> clsDriveBaseMid;
    shared_ptr<DigitalInput> clsDriveBaseFront;
    shared_ptr<DigitalOutput> dioTriggerDriveBaseLeft;
    shared_ptr<DigitalInput> dioEchoDriveBaseLeft;
    shared_ptr<Ultrasonic> ulsDriveBaseLeft;
    shared_ptr<Ultrasonic> ulsDriveBaseRight;

    //Intake and outake
    shared_ptr<frc::Talon> talIntakeOutakeRight;
    shared_ptr<frc::Talon> talIntakeOutakeLeft;
    shared_ptr<frc::Spark> spkRollerIntake;

    // Panel Affector Actuators
    shared_ptr<DoubleSolenoid> solPanelAffectorTop;
    shared_ptr<DoubleSolenoid> solPanelAffectorBottom;
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
