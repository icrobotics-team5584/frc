/*
 * SendableSparkMax.cpp
 *
 *  Created on: 21 Jan. 2021
 *      Author: Mitch
 */

#include "Utilities/SendableSparkMax.h"
#include "frc/smartdashboard/SendableRegistry.h"

SendableSparkMax::SendableSparkMax(int deviceID, MotorType type) :
  CANSparkMax(deviceID, type)
{
  _deviceID = deviceID;
}

void SendableSparkMax::InitSendable(frc::SendableBuilder& builder) {
  builder.SetSmartDashboardType("Speed Controller");
  builder.SetActuator(true);
  builder.SetSafeState([=]() { 
    CANSparkMax::Disable(); 
  });
  builder.AddDoubleProperty("Value",
                            [=]() {return CANSparkMax::Get();}, 
                            [=](double value) {CANSparkMax::Set(value);});
  
  frc::SendableRegistry::GetInstance().Add(this, "SendableSPM");
}