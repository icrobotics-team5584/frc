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
     _inst = nt::NetworkTableInstance::GetDefault();
     _table = _inst.GetTable("limelight");

    _controller.SetTolerance(100);
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

    if (frc::DriverStation::IsTeleopEnabled() && _shouldTrackTarget && _table->GetEntry("tv").GetDouble(0.0) == 1.0) {
        // TODO: Here is where we need to implement limelight target calculation.
        SetTargetRpm(GetLimelight().ty*100);
    }

}

void SubShooter::SetShooterTracking(bool enableTracking) {
    _shouldTrackTarget = enableTracking;
}

void SubShooter::SetTargetRpm(int rpm){
    _controllerF = (1.0f/5800.0f)* rpm;
    _controller.SetSetpoint(rpm);
}

void SubShooter::UpdatePidController() {
    double _output = _controller.Calculate(_encShooter1.GetVelocity()) + _controllerF;

    if (_output >= 0) {
        _spmShooter1.Set(_output);
        _visionVelocityOutput = _output;
    } else {
        _spmShooter1.Set(0);
        _visionVelocityOutput = 0;
    }
}
void SubShooter::Stop() {
    SetTargetRpm(0);
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

double SubShooter::GetVisionVelocityError() {
    return _visionVelocityOutput - _encShooter1.GetVelocity();
}