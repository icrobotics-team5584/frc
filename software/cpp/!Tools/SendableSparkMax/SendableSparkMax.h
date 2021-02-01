/*
 * SendableSparkMax.h
 *
 *  Created on: 21 Jan. 2021
 *      Author: Mitch
 */

#pragma once

#include <rev/CANSparkMax.h>
#include <frc/smartdashboard/Sendable.h>
#include <frc/smartdashboard/SendableBuilder.h>
#include <frc/smartdashboard/SendableBuilderImpl.h>

class SendableSparkMax :
public rev::CANSparkMax,
public frc::Sendable{
 public:
  SendableSparkMax(int deviceID, MotorType type);

 private:
  void InitSendable(frc::SendableBuilder& builder);
  int _deviceID;
};
