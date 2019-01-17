#include "RobotMap.h"
#include <AHRS.h>
#include <iostream>

RobotMap::RobotMap(){
    // DriveBase Actuators
    srxDriveBaseFrontRight.reset(new WPI_TalonSRX(can_srxDriveBaseFrontRight));
    srxDriveBaseFrontLeft.reset(new WPI_TalonSRX(can_srxDriveBaseFrontLeft));
    srxDriveBaseBackLeft.reset(new WPI_TalonSRX(can_srxDriveBaseBackLeft));
    srxDriveBaseBackRight.reset(new WPI_TalonSRX(can_srxDriveBaseBackRight));
    srxDriveBaseBackRight->Set(ControlMode::Follower, can_srxDriveBaseFrontRight);
    srxDriveBaseBackLeft->Set(ControlMode::Follower, can_srxDriveBaseFrontLeft);

    // Intake and Outake
    talIntakeOutakeRight.reset(new frc::Talon(pwm_talIntakeOutakeRight));
    talIntakeOutakeLeft.reset(new frc::Talon(pwm_talIntakeOutakeLeft));
    spkRollerIntake.reset(new frc::Spark(pwm_spkRollerIntake));


    // DriveBase Sensors
    ahrsNavXDriveBase.reset(new AHRS(SerialPort::kMXP));
    clsDriveBaseFront.reset(new DigitalInput(dio_clsDriveBaseFront));
    clsDriveBaseMid.reset(new DigitalInput(dio_clsDriveBaseMid));
    ulsDriveBaseLeft.reset(new Ultrasonic(dio_ulsTriggerDriveBaseLeft, dio_ulsEchoDriveBaseLeft));

    // Panel Affector Actuators
    solPanelAffectorTop.reset(new DoubleSolenoid(pcm_solPanelAffectorTopForward, pcm_solPanelAffectorTopReverse));
    solPanelAffectorBottom.reset(new DoubleSolenoid(pcm_solPanelAffectorBottomForward, pcm_solPanelAffectorBottomReverse));
    solPanelAffectorTopFinger.reset(new DoubleSolenoid(pcm_solPanelAffectorTopFingerForward, pcm_solPanelAffectorTopFingerReverse));
    solPanelAffectorBottomFinger.reset(new DoubleSolenoid(pcm_solPanelAffectorBottomFingerForward, pcm_solPanelAffectorBottomFingerReverse));
}