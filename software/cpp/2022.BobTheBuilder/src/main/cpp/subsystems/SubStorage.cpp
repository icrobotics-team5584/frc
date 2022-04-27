// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubStorage.h"
SubStorage::SubStorage()
{
    _spmStorage.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    _spmStorage.SetSmartCurrentLimit(20);
}

// This method will be called once per scheduler run
void SubStorage::Periodic()
{
    if (timer.Get().value() > 1)
    {
        _spmStorage.Set(0);
        timer.Stop();
        timer.Reset();
    }
    frc::Color detectedColorFront = DetectFrontBall();
    frc::SmartDashboard::PutNumber("RedFront", detectedColorFront.red);
    frc::SmartDashboard::PutNumber("GreenFront", detectedColorFront.green);
    frc::SmartDashboard::PutNumber("BlueFront", detectedColorFront.blue);

    frc::Color detectedColorBack = DetectBackBall();
    frc::SmartDashboard::PutNumber("RedBack", detectedColorBack.red);
    frc::SmartDashboard::PutNumber("GreenBack", detectedColorBack.green);
    frc::SmartDashboard::PutNumber("BlueBack", detectedColorBack.blue);
}

void SubStorage::In()
{
    timer.Stop();
    timer.Reset();
    _spmStorage.Set(0.8);
}

void SubStorage::Stop()
{
    _spmStorage.Set(0);
}

void SubStorage::DelayStop()
{
    timer.Reset();
    timer.Start();
}

void SubStorage::Out()
{
    timer.Stop();
    timer.Reset();
    _spmStorage.Set(-0.4);
}

void SubStorage::ExtendStopper()
{
    _solStopper.Set(frc::DoubleSolenoid::Value::kForward);
}

void SubStorage::RetractStopper()
{
    _solStopper.Set(frc::DoubleSolenoid::Value::kReverse);
}

frc::Color SubStorage::DetectFrontBall()
{
    frc::Color detectedColorFront = m_colorSensorFront.GetColor();
    if (detectedColorFront.red > 0.4)
    {
        return frc::Color::kRed;
    }
    if (detectedColorFront.blue > 0.4)
    {
        return frc::Color::kBlue;
    }
    else
        return frc::Color::kCornsilk; // return corn silk for no ball
}
frc::Color SubStorage::DetectBackBall()
{
    frc::Color detectedColorBack = m_colorSensorBack.GetColor();
    if (detectedColorBack.red > 0.4)
    {
        return frc::Color::kRed;
    }
    if (detectedColorBack.blue > 0.4)
    {
        return frc::Color::kBlue;
    }
    else
        return frc::Color::kCornsilk; // return corn silk for no ball
}
