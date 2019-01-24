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

    //Elevator
    srxElevator.reset(new WPI_TalonSRX(can_srxElevator));
    subElevatorLimitBottom.reset(new DigitalInput(lmt_subElevatorLimitBottom));
    subElevatorLimitTop.reset(new DigitalInput(lmt_subElevatorLimitTop));
    
    // Intake and Outake
    talIntakeOutake.reset(new frc::Talon(pwm_talIntakeOutake));
    spkRollerIntake.reset(new frc::Spark(pwm_spkRollerIntake));
    subIntakeOutakeCargo.reset(new DigitalInput(lmt_subIntakeOutakeCargo));

    // DriveBase Sensors
    ahrsNavXDriveBase.reset(new AHRS(SerialPort::kMXP));

    clsDriveBaseFront.reset(new DigitalInput(dio_clsDriveBaseFront));
    clsDriveBaseMid.reset(new DigitalInput(dio_clsDriveBaseMid));
    clsLineDriveBaseLeft.reset(new DigitalInput(dio_clsLineDriveBaseLeft));
    clsLineDriveBaseRight.reset(new DigitalInput(dio_clsLineDriveBaseRight));
    
    dioTriggerDriveBaseGimble.reset(new DigitalOutput(dio_ulsTriggerDriveBaseGimble));
    dioEchoDriveBaseGimble.reset(new DigitalInput(dio_ulsEchoDriveBaseGimble));
    dioTriggerDriveBaseBottom.reset(new DigitalOutput(dio_ulsTriggerDriveBaseBottom));
    dioEchoDriveBaseBottom.reset(new DigitalInput(dio_ulsEchoDriveBaseBottom));
    
    ulsDriveBaseGimble.reset(new Ultrasonic(dioTriggerDriveBaseGimble, dioEchoDriveBaseGimble));
    ulsDriveBaseBottom.reset(new Ultrasonic(dioTriggerDriveBaseBottom, dioEchoDriveBaseBottom));
    
    

    // Panel Affector Actuators
    solPanelAffectorTop.reset(new DoubleSolenoid(pcm_solPanelAffectorTopForward, pcm_solPanelAffectorTopReverse));
    solPanelAffectorBottom.reset(new DoubleSolenoid(pcm_solPanelAffectorBottomForward, pcm_solPanelAffectorBottomReverse));
    solPanelAffectorTopFinger.reset(new DoubleSolenoid(pcm_solPanelAffectorTopFingerForward, pcm_solPanelAffectorTopFingerReverse));
    solPanelAffectorBottomFinger.reset(new DoubleSolenoid(pcm_solPanelAffectorBottomFingerForward, pcm_solPanelAffectorBottomFingerReverse));

    //Gimble
    talGimble.reset(new frc::Talon(pwn_talGimble));
    subGimbleLimitLeft.reset(new DigitalInput(lmt_subGimbleLimitLeft));
    subGimbleLimitRight.reset(new DigitalInput(lmt_subGimbleLimitRight));
    anaGimblePot.reset(new AnalogInput(ana_potGimble));
}