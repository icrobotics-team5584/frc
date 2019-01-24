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
    can_srxDriveBaseBackLeft = 4,
    can_srxElevator = 5
};

enum PWM {
    pwm_talIntakeOutake = 0, 
    pwn_talGimble = 1,
    pwm_spkRollerIntake = 9999
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

enum LMT {
    lmt_subElevatorLimitBottom = 1,
    lmt_subElevatorLimitTop = 2,
    lmt_subGimbleLimitLeft = 3,
    lmt_subGimbleLimitRight = 4,
    lmt_subIntakeOutakeCargo = 5
};

class RobotMap {
private: 
public:
    RobotMap();

    // DriveBase Actuators
    shared_ptr<WPI_TalonSRX> srxDriveBaseFrontRight;
	shared_ptr<WPI_TalonSRX> srxDriveBaseFrontLeft;
    shared_ptr<WPI_TalonSRX> srxDriveBaseBackLeft;
	shared_ptr<WPI_TalonSRX> srxDriveBaseBackRight;

    //Elevator
    shared_ptr<WPI_TalonSRX> srxElevator;

    std::shared_ptr<DigitalInput> subElevatorLimitTop;
    std::shared_ptr<DigitalInput> subElevatorLimitBottom;

    //Gimble
    shared_ptr<frc::Talon> talGimble;

    std::shared_ptr<DigitalInput> subGimbleLimitLeft;
    std::shared_ptr<DigitalInput> subGimbleLimitRight;

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
    shared_ptr<frc::Talon> talIntakeOutake;
    shared_ptr<frc::Spark> spkRollerIntake;

    shared_ptr<DigitalInput> subIntakeOutakeCargo;

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
