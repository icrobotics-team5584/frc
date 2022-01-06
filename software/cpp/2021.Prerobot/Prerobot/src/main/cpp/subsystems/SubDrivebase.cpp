// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubDrivebase.h"

SubDrivebase::SubDrivebase()
{
    backLeft.Follow(frontLeft);
    backRight.Follow(frontRight);
};

// This method will be called once per scheduler run
void SubDrivebase::Periodic() {

}

void SubDrivebase::Drive(double speed, double steering)
{
    Diffdrive.ArcadeDrive(speed, steering);
}

void SubDrivebase::DollyDeploy(){
    solDolly.Set(frc::DoubleSolenoid::kForward);
}

void SubDrivebase::DollyRetract(){
    solDolly.Set(frc::DoubleSolenoid::kReverse); 
}
