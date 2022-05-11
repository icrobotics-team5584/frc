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
    
    frc::Color rawColorFront = m_colorSensorFront.GetColor();
    frc::SmartDashboard::PutNumber("RawRedFront", rawColorFront.red);
    frc::SmartDashboard::PutNumber("RawGreenFront", rawColorFront.green);
    frc::SmartDashboard::PutNumber("RawBlueFront", rawColorFront.blue);

    frc::Color rawColorBack = m_colorSensorBack.GetColor();
    frc::SmartDashboard::PutNumber("RawRedBack", rawColorBack.red);
    frc::SmartDashboard::PutNumber("RawGreenBack", rawColorBack.green);
    frc::SmartDashboard::PutNumber("RawBlueBack", rawColorBack.blue);

    _frontColorDisplayProperties ["colorWhenTrue"] = DetectFrontBall();
    _backColorDisplayProperties ["colorWhenTrue"] = DetectBackBall();
    

    _frontSensorWidget->WithProperties(_frontColorDisplayProperties);
    _backSensorWidget->WithProperties(_backColorDisplayProperties);
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

std::shared_ptr<nt::Value> SubStorage::DetectFrontBall()
{
    frc::Color detectedColorFront = m_colorSensorFront.GetColor();
    if (detectedColorFront.red > 0.4)
    {
        return _redName;
    }
    if (detectedColorFront.blue > 0.4)
    {
        return _blueName;
    }
    else
        return _greyName; 
}
std::shared_ptr<nt::Value> SubStorage::DetectBackBall()
{
    frc::Color detectedColorBack = m_colorSensorBack.GetColor();
    if (detectedColorBack.red > 0.4)
    {
        return _redName;
    }
    if (detectedColorBack.blue > 0.4)
    {
        return _blueName;
    }
    else
        return _greyName; 
}
