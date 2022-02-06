// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubShooter.h"

 // to make shooter 2 follow shooter 1
SubShooter::SubShooter(){
    _spmShooter1.SetSmartCurrentLimit(20);
    _spmShooter2.SetSmartCurrentLimit(20);
    _spmShooter1.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
    _spmShooter2.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
    _spmShooter1.SetInverted(true);
    _spmShooter2.Follow(_spmShooter1, true);
    frc::SmartDashboard::PutNumber("ShooterTargetVelocity", 0);

    frc::SmartDashboard::PutNumber("ShooterP", 0.001);
    frc::SmartDashboard::PutNumber("ShooterI", 0);
    frc::SmartDashboard::PutNumber("ShooterD", 0.00008);

    frc::SmartDashboard::PutNumber("ShooterF", _controllerF);
}

// This method will be called once per scheduler run
void SubShooter::Periodic() {
    _controller.SetPID(
        frc::SmartDashboard::GetNumber("ShooterP", 0),
        frc::SmartDashboard::GetNumber("ShooterI", 0),
        frc::SmartDashboard::GetNumber("ShooterD", 0)
    );
    _controllerF = (1.0f/5800.0f) * frc::SmartDashboard::GetNumber("ShooterTargetVelocity", 0);
    frc::SmartDashboard::PutNumber("Shooter Speed", _spmShooter1.Get());
    frc::SmartDashboard::PutNumber("Shooter Velocity", _encShooter1.GetVelocity());
    frc::SmartDashboard::PutNumber("ControllerF",_controllerF);
}

void SubShooter::Shoot(){
    double _output = _controller.Calculate(_encShooter1.GetVelocity(), frc::SmartDashboard::GetNumber("ShooterTargetVelocity", 0)) + _controllerF;
    if (_output >= 0) {
        _spmShooter1.Set(_output);
    } else {
        _spmShooter1.Set(0);
    }
    
}

void SubShooter::Stop() {
    _spmShooter1.Set(0);
}
 
 
