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

    subElevatorLimitBottom.reset(new DigitalInput(dio_subElevatorLimitBottom));
    subElevatorLimitTop.reset(new DigitalInput(dio_subElevatorLimitTop));
    
    // Intake and Outake
    srxIntakeOutake.reset(new WPI_TalonSRX(can_srxIntakeOutake));
    srxRollerIntake.reset(new WPI_TalonSRX(can_srxRollerIntake));
    subIntakeOutakeCargo.reset(new DigitalInput(dio_subIntakeOutakeCargo));

    // DriveBase Sensors
    ahrsNavXDriveBase.reset(new AHRS(SerialPort::kMXP));

    clsDriveBaseBackRight.reset(new DigitalInput(dio_clsDriveBaseBackRight));
    clsDriveBaseBackLeft.reset(new DigitalInput(dio_clsDriveBaseBackLeft));
    clsDriveBaseMidRight.reset(new DigitalInput(dio_clsDriveBaseMidRight));
    clsDriveBaseMidLeft.reset(new DigitalInput(dio_clsDriveBaseMidLeft));
    
    dioTriggerDriveBaseGimble.reset(new DigitalOutput(dio_ulsTriggerDriveBaseGimble));
    dioEchoDriveBaseGimble.reset(new DigitalInput(dio_ulsEchoDriveBaseGimble));
    dioTriggerDriveBaseBottom.reset(new DigitalOutput(dio_ulsTriggerDriveBaseBottom));
    dioEchoDriveBaseBottom.reset(new DigitalInput(dio_ulsEchoDriveBaseBottom));
    
    ulsDriveBaseGimble.reset(new Ultrasonic(dioTriggerDriveBaseGimble, dioEchoDriveBaseGimble));
    ulsDriveBaseBottom.reset(new Ultrasonic(dioTriggerDriveBaseBottom, dioEchoDriveBaseBottom));
    
    

    // Panel Affector Actuators
    solPanelAffectorTop.reset(new DoubleSolenoid(pcm_lower, pcm_solPanelAffectorTopForward, pcm_solPanelAffectorTopReverse));
    solPanelAffectorBottom.reset(new DoubleSolenoid(pcm_lower, pcm_solPanelAffectorBottomForward, pcm_solPanelAffectorBottomReverse));
    solPanelAffectorTopFinger.reset(new DoubleSolenoid(pcm_lower, pcm_solPanelAffectorTopFingerForward, pcm_solPanelAffectorTopFingerReverse));
    solPanelAffectorBottomFinger.reset(new DoubleSolenoid(pcm_lower, pcm_solPanelAffectorBottomFingerForward, pcm_solPanelAffectorBottomFingerReverse));

    //Gimble
    srxGimble.reset(new WPI_TalonSRX(can_srxGimble));
    subGimbleLimitLeft.reset(new DigitalInput(dio_subGimbleLimitLeft));
    subGimbleLimitRight.reset(new DigitalInput(dio_subGimbleLimitRight));
    subGimblePot.reset(new AnalogInput(ana_potGimble));
}