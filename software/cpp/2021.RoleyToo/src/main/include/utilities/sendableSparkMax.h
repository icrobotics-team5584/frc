// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <rev/CANSparkMax.h>
#include <frc/smartdashboard/Sendable.h>
#include <frc/smartdashboard/SendableBuilder.h>
#include <frc/smartdashboard/SendableBuilderImpl.h>

class sendableSparkMax :
public rev::CANSparkMax,
public frc::Sendable
{
 public:
  sendableSparkMax(int deviceID, MotorType type);

 private:
  void InitSendable(frc::SendableBuilder& builder);
  int _deviceID;
};
