#include "RobotMap.h"
#include <AHRS.h>
#include <iostream>

RobotMap::RobotMap(){
    // DriveBase Actuators
    srxDriveBaseFrontLeft.reset(new WPI_TalonSRX(can_srxDriveBaseFrontLeft));
    srxDriveBaseBackLeft.reset(new WPI_TalonSRX(can_srxDriveBaseBackLeft));
    srxDriveBaseFrontRight.reset(new WPI_TalonSRX(can_srxDriveBaseFrontRight));
    srxDriveBaseBackRight.reset(new WPI_TalonSRX(can_srxDriveBaseBackRight));
    srxDriveBaseBackLeft->Set(ControlMode::Follower, can_srxDriveBaseFrontLeft);
    srxDriveBaseBackRight->Set(ControlMode::Follower, can_srxDriveBaseFrontRight);

    //Elevator
    srxElevatorMaster.reset(new WPI_TalonSRX(can_srxElevatorMaster));
    srxElevatorSlave.reset(new WPI_TalonSRX(can_srxElevatorSlave));
    srxElevatorSlave->Set(ControlMode::Follower, can_srxElevatorMaster);

    subElevatorLimitBottom.reset(new DigitalInput(lmt_subElevatorLimitBottom));
    subElevatorLimitTop.reset(new DigitalInput(lmt_subElevatorLimitTop));
    
    // Intake and Outake
    srxIntakeOutake.reset(new WPI_TalonSRX(can_srxIntakeOutake));
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
    srxGimble.reset(new WPI_TalonSRX(can_srxGimble));
    subGimbleLimitLeft.reset(new DigitalInput(lmt_subGimbleLimitLeft));
    subGimbleLimitRight.reset(new DigitalInput(lmt_subGimbleLimitRight));
    subGimblePot.reset(new AnalogInput(ana_potGimble));
}