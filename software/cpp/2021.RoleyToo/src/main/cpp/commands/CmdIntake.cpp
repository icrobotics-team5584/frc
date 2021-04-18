// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdIntake.h"
#include "frc/smartdashboard/SmartDashboard.h"

CmdIntake::CmdIntake(SubStorage* subStorage, SubIntake* subIntake) {
  // Use addRequirements() here to declare subsystem dependencies.
  _subStorage = subStorage;
  _subIntake = subIntake;
  //frc::SmartDashboard::PutData("Storage PID", &_storagePID);
  frc::SmartDashboard::PutNumber("Storage Setpoint", Setpoint);
  frc::SmartDashboard::PutNumber("Storage P", StorageP);
  frc::SmartDashboard::PutNumber("Storage I", StorageI);
  frc::SmartDashboard::PutNumber("Storage D", StorageD);
  frc::SmartDashboard::PutNumber("Storage FF", StorageF);
}

// Called when the command is initially scheduled.
void CmdIntake::Initialize() {
  _timer.Reset();
  _timer.Start();

  _delayIntake.Reset();
  _delayIntake.Start();
}

// Called repeatedly when this Command is scheduled to run
void CmdIntake::Execute() {  
  _subIntake->Intake();
}

// Called once the command ends or is interrupted.
void CmdIntake::End(bool interrupted) {
  std::cout << "running CmdIntake::End()" << std::endl;
  _subIntake->Stop();
}

// Returns true when the command should end.
bool CmdIntake::IsFinished() {
  return false;
}
