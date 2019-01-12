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

    // DriveBase Sensors
    ahrsNavXDriveBase.reset(new AHRS(SerialPort::kMXP));
    clsDriveBaseFront.reset(new DigitalInput(dio_clsDriveBaseFront));
    clsDriveBaseMid.reset(new DigitalInput(dio_clsDriveBaseMid));
    ulsDriveBaseLeft.reset(new Ultrasonic(dio_ulsTriggerDriveBaseLeft, dio_ulsEchoDriveBaseLeft));

    // Panel Affector Actuators
    solPanelAffectorTopLeft.reset(new DoubleSolenoid(pcm_solPanelAffectorTopLeftForward, pcm_solPanelAffectorTopLeftReverse));
    solPanelAffectorTopRight.reset(new DoubleSolenoid(pcm_solPanelAffectorTopRightForward, pcm_solPanelAffectorTopRightReverse));
    solPanelAffectorBottomLeft.reset(new DoubleSolenoid(pcm_solPanelAffectorBottomLeftForward, pcm_solPanelAffectorBottomLeftReverse));
    solPanelAffectorBottomRight.reset(new DoubleSolenoid(pcm_solPanelAffectorBottomRightForward, pcm_solPanelAffectorBottomRightReverse));
}