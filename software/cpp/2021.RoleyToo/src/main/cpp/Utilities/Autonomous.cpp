// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Utilities/Autonomous.h"

Autonomous::Autonomous(){
    notifier.StartPeriodic(fasterPeriod);
}

void Autonomous::Periodic(){
    std::cout<<"Auto periodic"<<std::endl;
}