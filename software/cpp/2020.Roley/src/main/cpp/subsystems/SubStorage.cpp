/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SubStorage.h"
#include "RobotMap.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include <frc/shuffleboard/Shuffleboard.h>
#include "Robot.h"


SubStorage::SubStorage() : Subsystem("ExampleSubsystem"), lbrTopStorage(0){
  
  // Create and set motors controllers to default settings
  srxStorage.reset(new TalonSRX(can_srxStorage));
  solStorageActuator.reset(new DoubleSolenoid(pcm_solStorageForward, pcm_solStorageRetract));
  srxBottomRoller.reset(new TalonSRX(can_srxStorageRoller));
  //spmBottomRoller->RestoreFactoryDefaults();
  //spmBottomRoller->SetSmartCurrentLimit(30);

  lbrBottom.reset(new frc::DigitalInput(dio_StorageBottom));
  lbrTop.reset(new frc::DigitalInput(dio_StorageTop));
  lbrGap.reset(new frc::DigitalInput(dio_StorageGap));

  // Setup shuffleboard values
  frc::SmartDashboard::PutNumber("Feeder speed", _speed);
  nteBottomRollerSpeed = frc::Shuffleboard::GetTab(kShuffleBoardSettingsTab)
    .Add("Bottom Roller Speed", kDefaultBottomRollerSpeed) 
    .GetEntry();
  nteBottomRollerReverseSpeed = frc::Shuffleboard::GetTab(kShuffleBoardSettingsTab)
    .Add("Bottom Roller Reverse Speed", kDefaultBottomRollerSpeed) 
    .GetEntry();
}

void SubStorage::InitDefaultCommand() {
  
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

void SubStorage::Periodic(){
  //frc::Shuffleboard::GetTab(kShuffleBoardSettingsTab)
  //  .Add("Bottom Linebreak", lbrBottom->Get());
  frc::SmartDashboard::PutBoolean("Storage Bottom Linebreak", lbrBottom->Get());
  frc::SmartDashboard::PutBoolean("Storage Top Linebreak", lbrTop->Get());
  frc::SmartDashboard::PutBoolean("Storage Gap Linebreak", lbrGap->Get());
}

void SubStorage::Forward(){
  _speed = frc::SmartDashboard::GetNumber("Feeder speed", _speed);
  srxStorage->Set(ControlMode::PercentOutput, _speed);
}

void SubStorage::Backward(){
  _speed = frc::SmartDashboard::GetNumber("Feeder speed", _speed);
  srxStorage->Set(ControlMode::PercentOutput, -_speed);
}

void SubStorage::BottomRollerForward(){
  std::cout << "roller in " << nteBottomRollerSpeed.GetDouble(kDefaultBottomRollerSpeed) << std::endl;
  srxBottomRoller->Set(ControlMode::PercentOutput, nteBottomRollerSpeed.GetDouble(kDefaultBottomRollerSpeed));
}

void SubStorage::BottomRollerBackward(){
    std::cout << "roller out " << nteBottomRollerSpeed.GetDouble(kDefaultBottomRollerSpeed) << std::endl;
  srxBottomRoller->Set(ControlMode::PercentOutput, nteBottomRollerReverseSpeed.GetDouble(kDefaultBottomRollerReverseSpeed));
}

void SubStorage::BottomRollerStop() {
  srxBottomRoller->Set(ControlMode::PercentOutput, 0);  
}

void SubStorage::Stop(){
  srxStorage->Set(ControlMode::PercentOutput, 0);
}

bool SubStorage::GetLbrTopStorage(){
  return lbrTopStorage.Get();
}

bool SubStorage::lbrBottomIsBlocked(){
  return !lbrBottom->Get();
}

bool SubStorage::lbrTopIsBlocked(){
  return !lbrTop->Get();
}

bool SubStorage::lbrStorageHasGap(){
  return lbrGap->Get();
}

void SubStorage::Expand(){
  solStorageActuator->Set(frc::DoubleSolenoid::kForward);
}

void SubStorage::Retract(){
  solStorageActuator->Set(frc::DoubleSolenoid::kReverse);
}

void SubStorage::SetSpeed(double speed){
  speedSet = speed;
  srxStorage->Set(ControlMode::PercentOutput, speedSet);
}


// Put methods for controlling this subsystem
// here. Call these from Commands.
