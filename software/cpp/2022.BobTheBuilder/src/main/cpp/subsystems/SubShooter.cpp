// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubShooter.h"
#include "math.h"

 // to make shooter 2 follow shooter 1
SubShooter::SubShooter(){
    _spmShooter1.SetSmartCurrentLimit(20);
    _spmShooter2.SetSmartCurrentLimit(20);
    _spmShooter1.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
    _spmShooter2.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
    _spmShooter1.SetInverted(true);
    _spmShooter2.Follow(_spmShooter1, true);
     _inst = nt::NetworkTableInstance::GetDefault();
     _table = _inst.GetTable("limelight");

    _controller.SetTolerance(50);
    frc::SmartDashboard::PutNumber("LIME_LIGHT_angleAdjust",0); //Used to adjust the limelight 'ty' vertical off target angle.
}

// This method will be called once per scheduler run
void SubShooter::Periodic() {
    frc::SmartDashboard::PutNumber("Shooter Velocity", _encShooter1.GetVelocity());
    frc::SmartDashboard::PutNumber("ShooterTargetSpeed",_controller.GetSetpoint());

    _tx = _table->GetEntry("tx");
    _ty = _table->GetEntry("ty");
    _thor = _table->GetEntry("thor");
    _tvert = _table->GetEntry("tvert");
    UpdatePidController();

    if (_shootingLow && _shouldTrackTarget) {
        SetTargetRpm(1200);
    } else {
        if (/*frc::DriverStation::IsTeleopEnabled() &&*/ _shouldTrackTarget && _table->GetEntry("tv").GetDouble(0.0) == 1.0) {
            // In telep, tracking target and target is visible
            // https://mycurvefit.com/
            double x = GetLimelight().ty + (frc::SmartDashboard::GetNumber("LIME_LIGHT_angleAdjust",0)); //Gets the vertical off target angle from limelight ‘ty’ and adds adjustment.
            double out = 2106.346 - 42.59286*x + 1.897089*pow(x,2) + 0.1338984*pow(x,3);
            if(out > 3000){
                out = 3000;
            }
            _lastspeed = out;
            SetTargetRpm(out);
            // SetTargetRpm(frc::SmartDashboard::GetNumber("ShooterSetRPM", 0));
        } else if (frc::DriverStation::IsTeleopEnabled() && _shouldTrackTarget) {
            // in teleop, tracking target and target is not visible
            
            SetTargetRpm(_lastspeed);    
        } else {
            //SetTargetRpm(0);
        }
    }

    frc::SmartDashboard::PutBoolean("Low Mode",_shootingLow);
    frc::SmartDashboard::PutBoolean("Should Track Target",_shouldTrackTarget);

}

void SubShooter::SetShooterTracking(bool enableTracking) {
    _shouldTrackTarget = enableTracking;
}

void SubShooter::SetTargetRpm(double rpm){
    _controller.SetSetpoint(rpm);
}

void SubShooter::UpdatePidController() {
    double feedForward = (1.0f/5300.0f)* _controller.GetSetpoint();
    double _output = _controller.Calculate(_encShooter1.GetVelocity()) + feedForward;
    if (_output >= 0) {
        _spmShooter1.SetVoltage(units::volt_t(_output*12));
    } else {
        _spmShooter1.Set(0);
    }
}
void SubShooter::Stop() {
    SetTargetRpm(0);
    _shouldTrackTarget = false;
}
 
LimelightData SubShooter::GetLimelight() {
    return LimelightData(
        SubShooter::_tx.GetDouble(0),
        SubShooter::_ty.GetDouble(0),
        SubShooter::_thor.GetDouble(0),
        SubShooter::_tvert.GetDouble(0)
    );
    
}
bool SubShooter::IsAtTargetSpeed() {
    return _controller.AtSetpoint();
    
}

void SubShooter::TogglePosition() {
    
    if (_shootingLow) {
        _shootingLow = false;

    } else {
        _shootingLow = true;
    }

}

bool SubShooter::GetLowMode() {
    return _shootingLow;
}

void SubShooter::SetLowMode(bool lowMode) {
    _shootingLow = lowMode;
}

