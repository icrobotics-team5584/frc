#pragma once

#include "ctre/Phoenix.h"

/* FollowerProfileConfiguration inherits TalonSRXConfiguration so it has all the default configs + the unique configs for the follower talon */
class FollowerProfileConfiguration : public TalonSRXConfiguration
{
public:
    FollowerProfileConfiguration() : TalonSRXConfiguration()
    {
        primaryPID.selectedFeedbackSensor = FeedbackDevice::QuadEncoder;
        // primaryPID.selectedFeedbackSensor = FeedbackDevice::CTRE_MagEncoder_Relative;
        neutralDeadband = 0.001; /* 0.1% super small for best low-speed control */
    }
};