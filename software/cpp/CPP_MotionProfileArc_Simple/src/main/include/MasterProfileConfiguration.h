#pragma once

#include "ctre/Phoenix.h"

/* MasterProfileConfiguration inherits TalonSRXConfiguration so it has all the default configs + the unique configs for the master talon */
class MasterProfileConfiguration : public TalonSRXConfiguration
{
public:
    /* Constructor takes a talon and pigeon so it can reference it with their ID */
    MasterProfileConfiguration(TalonSRX *otherTalon, PigeonIMU *pigeon) : TalonSRXConfiguration()
    {
        /* Primary PID will be the sensor sum so it includes both sides */
        primaryPID.selectedFeedbackSensor = FeedbackDevice::SensorSum;
        /* Auxiliary PID will be RemoteSensor0 which is the Pigeon */
        auxiliaryPID.selectedFeedbackSensor = FeedbackDevice::RemoteSensor1;
        neutralDeadband = 0.001; /* 0.1% super small for best low-speed control */

        /* Find these gains in Phoenix Tuner first and later put them here */
        slot0.kF = 0.35;
        slot0.kP = 0.8;
        slot0.kI = 0.0;
        slot0.kD = 80;
        slot0.integralZone = 400;
        slot0.closedLoopPeakOutput = 1.0;

        slot1.kF = 0;
        slot1.kP = 1.0;
        slot1.kI = 0.0;
        slot1.kD = 0.0;
        slot1.integralZone = 400;
        slot1.closedLoopPeakOutput = 0.5;

        /* Remote Sensor 0 is the other talon's quadrature encoder */
        remoteFilter0.remoteSensorSource = RemoteSensorSource::RemoteSensorSource_TalonSRX_SelectedSensor;
        remoteFilter0.remoteSensorDeviceID = otherTalon->GetDeviceID();

        /* Remote Sensor 1 is the Pigeon over CAN */
        remoteFilter1.remoteSensorSource = RemoteSensorSource::RemoteSensorSource_Pigeon_Yaw;
        remoteFilter1.remoteSensorDeviceID = pigeon->GetDeviceNumber();

        /* Configure sensor sum to be this quad encoder and the other talon's encoder */
        sum0Term = FeedbackDevice::QuadEncoder;
        sum1Term = FeedbackDevice::RemoteSensor0;

        /* Configure auxPIDPolarity to match the drive train */
        auxPIDPolarity = false;
    }
};