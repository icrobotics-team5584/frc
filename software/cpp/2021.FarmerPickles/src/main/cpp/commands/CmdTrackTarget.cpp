// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdTrackTarget.h"
#include "frc/smartdashboard/SmartDashboard.h"

CmdTrackTarget::CmdTrackTarget(SubTurret* subTurret) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subTurret = subTurret;
}

// Called when the command is initially scheduled.
void CmdTrackTarget::Initialize() {    
    frc::SmartDashboard::PutData("PID", &turretPID);
  }

// Called repeatedly when this Command is scheduled to run
void CmdTrackTarget::Execute() {

  //LEFT POSITIVE, RIGHT NEGATIVE

  int PIDOutput = turretPID.Calculate(_subTurret->GetX());

  if ((_subTurret->getTurretAngle() < 5 && PIDOutput > 0 ) || (_subTurret->getTurretAngle() > 100 && PIDOutput < 0 )) {
    PIDOutput = 0;
  }

  _subTurret->setTurret(PIDOutput);

}

// Called once the command ends or is interrupted.
void CmdTrackTarget::End(bool interrupted) {}

// Returns true when the command should end.
bool CmdTrackTarget::IsFinished() {
  return false;
}
