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
    srxRollerIntakeBar.reset(new WPI_TalonSRX(can_srxRollerIntakeBar));
    // subIntakeOutakeCargo.reset(new DigitalInput(dio_subIntakeOutakeCargo));

    // DriveBase Sensors
    ahrsNavXDriveBase.reset(new AHRS(SPI::kMXP));

    clsDriveBaseRight.reset(new DigitalInput(dio_clsDriveBaseRight));
    clsDriveBaseLeft.reset(new DigitalInput(dio_clsDriveBaseLeft));
    // clsDriveBaseMidRight.reset(new DigitalInput(dio_clsDriveBaseMidRight));
    // clsDriveBaseMidLeft.reset(new DigitalInput(dio_clsDriveBaseMidLeft));
    
    dioEchoDriveBaseLeft.reset(new DigitalInput(dio_ulsEchoLeft));
    dioTriggerDriveBaseLeft.reset(new DigitalOutput(dio_ulsTriggerLeft));
    dioEchoDriveBaseRight.reset(new DigitalInput(dio_ulsEchoRight));
    dioTriggerDriveBaseRight.reset(new DigitalOutput(dio_ulsTriggerRight));
    
    dioUlsDriveBaseLeft.reset(new Ultrasonic(dioTriggerDriveBaseLeft, dioEchoDriveBaseLeft));
    dioUlsDriveBaseRight.reset(new Ultrasonic(dioTriggerDriveBaseRight, dioEchoDriveBaseRight));
    
    

    // Panel Affector Actuators
    solPanelAffectorTop.reset(new DoubleSolenoid(pcm_lower, pcm_solPanelAffectorTopForward, pcm_solPanelAffectorTopReverse));
    solPanelAffectorBottom.reset(new DoubleSolenoid(pcm_lower, pcm_solPanelAffectorBottomForward, pcm_solPanelAffectorBottomReverse));
    solPanelAffectorTopFinger.reset(new DoubleSolenoid(pcm_lower, pcm_solPanelAffectorTopFingerForward, pcm_solPanelAffectorTopFingerReverse));
    //solPanelAffectorBottomFinger.reset(new DoubleSolenoid(pcm_lower, pcm_solPanelAffectorBottomFingerForward, pcm_solPanelAffectorBottomFingerReverse));

    //Gimble
    srxGimble.reset(new WPI_TalonSRX(can_srxGimble));
    subGimbleLimitLeft.reset(new DigitalInput(dio_subGimbleLimitLeft));
    subGimbleLimitRight.reset(new DigitalInput(dio_subGimbleLimitRight));
    subGimblePot.reset(new AnalogInput(ana_potGimble));

    //climber
    spxClimber.reset(new VictorSPX(can_spxClimber));
    spxClimberSlave.reset(new VictorSPX(can_spxClimberSlave));
    srvClimberLatch.reset(new Servo(pwm_srvClimberLatch));
    limClimberLimit.reset(new DigitalInput(dio_limClimberLimit));
    
}