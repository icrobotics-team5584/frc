// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "sendableSparkMax.h"

sendableSparkMax::sendableSparkMax(int deviceID, MotorType type) :
    CANSparkMax(deviceID, type)
{}

void sendableSparkMax::InitSendable(frc::SendableBuilder& builder) {
    builder.SetSmartDashboardType("Speed Controller");
    builder.SetActuator(true);
    builder.SetSafeState([=]() { CANSparkMax::Disable(); });
    builder.AddDoubleProperty(
        "Value",
        [=]() { return CANSparkMax::Get(); },
        [=](double value) { CANSparkMax::Set(value); }
    );
    
}