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
  int PIDOutput;

  if (_subTurret->CheckTarget()) {
      failureCount = 0;
      std::cout << "VIS: 1"; 
      PIDOutput = turretPID.Calculate(_subTurret->GetX());
  }
  else {
    failureCount++;
    std::cout << "VIS: 0";
    if (failureCount > 35) {
      PIDOutput = turretPID.Calculate(40 - _subTurret->getTurretAngle());
    }
  }

  if ((_subTurret->getTurretAngle() < 10) && (PIDOutput > 0)) { PIDOutput = 0; }
  if ((_subTurret->getTurretAngle() > 100) && (PIDOutput < 0)) { PIDOutput = 0; }

  std::cout << " PID: " << PIDOutput;
  std::cout << " LMT: " << _subTurret->GetSwitch();
  std::cout << " FLC: " << failureCount;
  std::cout << " ANG: " << _subTurret->getTurretAngle() << "\n";
  _subTurret->setTurret(PIDOutput);

}

// Called once the command ends or is interrupted.
void CmdTrackTarget::End(bool interrupted) {
  _subTurret->setTurret(0);
}

// Returns true when the command should end.
bool CmdTrackTarget::IsFinished() {
  return false;
}
