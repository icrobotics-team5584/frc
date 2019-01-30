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
    can_srxDriveBaseFrontLeft = 1,
    can_srxDriveBaseBackLeft = 2,
    can_srxDriveBaseFrontRight = 3,
    can_srxDriveBaseBackRight = 4,
};

enum PWM {
    pwm_talIntakeOutakeRight = 1, 
    pwm_talIntakeOutakeLeft = 0,   
    pwm_spkRollerIntake = 2
};

enum DIO {
    dio_clsDriveBaseFront = 0,
    dio_clsDriveBaseMid = 1,
    dio_ulsTriggerDriveBaseGimble = 2,
    dio_ulsEchoDriveBaseGimble = 3,
    dio_ulsTriggerDriveBaseBottom = 4,
    dio_ulsEchoDriveBaseBottom = 5,
    dio_clsLineDriveBaseLeft = 6,
    dio_clsLineDriveBaseRight = 7,
};

enum Analog {
};

enum PCM {
    pcm_solPanelAffectorTopFingerForward = 7,
    pcm_solPanelAffectorTopFingerReverse = 6,
    pcm_solPanelAffectorBottomFingerForward = 5,
    pcm_solPanelAffectorBottomFingerReverse = 4,

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
    shared_ptr<DigitalOutput> dioTriggerDriveBaseGimble;
    shared_ptr<DigitalInput> dioEchoDriveBaseGimble;
    shared_ptr<DigitalOutput> dioTriggerDriveBaseBottom;
    shared_ptr<DigitalInput> dioEchoDriveBaseBottom;
    shared_ptr<Ultrasonic> ulsDriveBaseGimble;
    shared_ptr<Ultrasonic> ulsDriveBaseBottom;
    shared_ptr<DigitalInput> clsLineDriveBaseLeft;
    shared_ptr<DigitalInput> clsLineDriveBaseRight;

    //Intake and outake
    shared_ptr<frc::Talon> talIntakeOutakeRight;
    shared_ptr<frc::Talon> talIntakeOutakeLeft;
    shared_ptr<frc::Spark> spkRollerIntake;

    // Panel Affector Actuators
    shared_ptr<DoubleSolenoid> solPanelAffectorTop;
    shared_ptr<DoubleSolenoid> solPanelAffectorBottom;
    shared_ptr<DoubleSolenoid> solPanelAffectorTopFinger;
    shared_ptr<DoubleSolenoid> solPanelAffectorBottomFinger;
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
