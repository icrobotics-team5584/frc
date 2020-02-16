/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Utilities/EncoderTalon.h"

EncoderTalon::EncoderTalon(TalonSRX *talon) {
    _talon = talon;
}

double EncoderTalon::GetEncoderValue() {
    return _talon->GetSelectedSensorPosition();
}

void EncoderTalon::ResetEncoder(){
    _talon->SetSelectedSensorPosition(0.0);
}