// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubShooter.h"

 // to make shooter 2 follow shooter 1
SubShooter::SubShooter(){

_spmShooter2.Follow(_spmShooter1);
}

// This method will be called once per scheduler run
void SubShooter::Periodic() {
}

void SubShooter::Shoot(){
_spmShooter1.Set(.7);
}
 
 