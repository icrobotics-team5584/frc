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
    can_srxGimble = 5,
    can_srxIntakeOutake = 6,
    can_srxElevatorMaster = 7,
    can_srxElevatorSlave = 8,
    can_srxRollerIntake = 9,
    can_srxRollerIntakeBar = 10,
    can_spxClimber = 51,
    can_spxClimberSlave = 52
};

enum PWM {
    pwm_srvClimberLatch = 0
};

enum DIO {
    dio_clsDriveBaseBackRight = 0,
    dio_clsDriveBaseBackLeft = 1,
    dio_clsDriveBaseMidRight = 2,
    dio_clsDriveBaseMidLeft = 3,
    dio_ulsTriggerLeft = 20,
    dio_ulsEchoLeft = 19,
    dio_ulsTriggerRight = 4,
    dio_ulsEchoRight = 5,
    dio_subGimbleLimitLeft = 6,
    dio_subGimbleLimitRight = 7,
    dio_subElevatorLimitBottom = 8,
    dio_subElevatorLimitTop = 9,
    // dio_subIntakeOutakeCargo = 10
    dio_limClimberLimit = 10
};

enum Analog {
    ana_potGimble = 0,
};

enum PCM {
    pcm_lower = 0,
    pcm_upper = 1
};

enum PCM_0{
    pcm_solPanelAffectorTopFingerForward = 1,
    pcm_solPanelAffectorTopFingerReverse = 0,

    //pcm_solPanelAffectorBottomFingerForward = 9999,
    //pcm_solPanelAffectorBottomFingerReverse = 9999,
    
    pcm_solPanelAffectorTopForward = 7,
    pcm_solPanelAffectorTopReverse = 6,
    pcm_solPanelAffectorBottomForward = 5,
    pcm_solPanelAffectorBottomReverse = 4
};

enum PCM_1 {
   // pcm_solPanelAffectorTopFingerForward = 1,
   // pcm_solPanelAffectorTopFingerReverse = 0,
   // pcm_solPanelAffectorBottomFingerForward = 9999,
   // pcm_solPanelAffectorBottomFingerReverse = 9999,
//
   // pcm_solPanelAffectorTopForward = 7,
   // pcm_solPanelAffectorTopReverse = 6,
   // pcm_solPanelAffectorBottomForward = 5,
   // pcm_solPanelAffectorBottomReverse = 4
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
    shared_ptr<WPI_TalonSRX> srxElevatorMaster;
    shared_ptr<WPI_TalonSRX> srxElevatorSlave;
    shared_ptr<DigitalInput> subElevatorLimitTop;
    shared_ptr<DigitalInput> subElevatorLimitBottom;

    //Gimble
    shared_ptr<WPI_TalonSRX> srxGimble;

    shared_ptr<DigitalInput> subGimbleLimitLeft;
    shared_ptr<DigitalInput> subGimbleLimitRight;

    shared_ptr<AnalogInput> subGimblePot;

    // DriveBase Sensors
    shared_ptr<AHRS> ahrsNavXDriveBase;
    shared_ptr<DigitalInput> clsDriveBaseBackLeft;
    shared_ptr<DigitalInput> clsDriveBaseBackRight;
    shared_ptr<DigitalInput> clsDriveBaseMidLeft;
    shared_ptr<DigitalInput> clsDriveBaseMidRight;
    shared_ptr<DigitalOutput> dioTriggerDriveBaseLeft;
    shared_ptr<DigitalInput> dioEchoDriveBaseLeft;
    shared_ptr<DigitalOutput> dioTriggerDriveBaseRight;
    shared_ptr<DigitalInput> dioEchoDriveBaseRight;
    shared_ptr<Ultrasonic> dioUlsDriveBaseLeft;
    shared_ptr<Ultrasonic> dioUlsDriveBaseRight;

    //Intake and outake
    shared_ptr<WPI_TalonSRX> srxIntakeOutake;
    shared_ptr<WPI_TalonSRX> srxRollerIntake;
    shared_ptr<WPI_TalonSRX> srxRollerIntakeBar;

    // shared_ptr<DigitalInput> subIntakeOutakeCargo;

    // Panel Affector Actuators
    shared_ptr<DoubleSolenoid> solPanelAffectorTop;
    shared_ptr<DoubleSolenoid> solPanelAffectorBottom;
    shared_ptr<DoubleSolenoid> solPanelAffectorTopFinger;
    //shared_ptr<DoubleSolenoid> solPanelAffectorBottomFinger;
    
    //climber
    shared_ptr<VictorSPX> spxClimber;
    shared_ptr<VictorSPX> spxClimberSlave;
    shared_ptr<Servo> srvClimberLatch;
    shared_ptr<DigitalInput> limClimberLimit;
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
