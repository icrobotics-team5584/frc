/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SubClimber.h"

SubClimber::SubClimber() : Subsystem("ExampleSubsystem") {

  srxClimberLeft.reset(new WPI_TalonSRX(can_srxClimberLeft));
  srxClimberRight.reset(new WPI_TalonSRX(can_srxClimberRight)); 
  SolLock1.reset(new frc::DoubleSolenoid(0,1));
  SolLock2.reset(new frc::DoubleSolenoid(2,3));
  LimitClimbUp.reset(new frc::DigitalInput(0));
  LimitClimbDown.reset(new frc::DigitalInput(1));

  srxClimberLeft->ConfigFactoryDefault();
  srxClimberRight->ConfigFactoryDefault();
  srxClimberLeft->SetSensorPhase(false);
  srxClimberRight->Set(ControlMode::Follower, can_srxClimberLeft);
  
  srxClimberRight->SetInverted(true);
  srxClimberLeft->SetInverted(false);

  srxClimberLeft->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Absolute);
}

void SubClimber::Periodic(){
  frc::SmartDashboard::PutBoolean("Limit switch DOWN", LimitClimbDownGet());
  frc::SmartDashboard::PutBoolean("Limit switch UP", LimitClimbUpGet());
  _speed = frc::SmartDashboard::GetNumber("Climber Speed", _speed);
  frc::SmartDashboard::PutNumber("Climber Speed", _speed);
}

void SubClimber::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

void SubClimber::MoveUp(){
  srxClimberLeft->Set(_speed);
}

void SubClimber::MoveDown(){
  //srxClimberLeft->Set(-_speed);
}

void SubClimber::Stop(){
  srxClimberLeft->Set(0);
}

void SubClimber::Lock(){
  SolLock1->Set(frc::DoubleSolenoid::kForward);
  SolLock2->Set(frc::DoubleSolenoid::kForward);

}

void SubClimber::Unlock(){
  SolLock1->Set(frc::DoubleSolenoid::kReverse);
  SolLock2->Set(frc::DoubleSolenoid::kReverse);
}

bool SubClimber::LimitClimbUpGet(){
  return !LimitClimbUp->frc::DigitalInput::Get();
}

bool SubClimber::LimitClimbDownGet(){
  return !LimitClimbDown->frc::DigitalInput::Get();
}


void SubClimber::ConfigTalonOverride(){
  srxClimberLeft->SelectProfileSlot(0, 0);
  srxClimberLeft->Config_kF(0, 0, 0);
  srxClimberLeft->Config_kP(0, 0, 0);
  srxClimberLeft->Config_kI(0, 0, 0);
  srxClimberLeft->Config_kD(0, 0, 0);
  
  srxClimberLeft->ConfigPeakOutputForward(0.6, 0);
  srxClimberLeft->ConfigPeakOutputReverse(-0.6, 0);
}

void SubClimber::ConfigTalon()  //Generic Talon PID Config, has kI
{

  srxClimberLeft->SetStatusFramePeriod(StatusFrameEnhanced::Status_13_Base_PIDF0, 10, 10);
  srxClimberLeft->SetStatusFramePeriod(StatusFrameEnhanced::Status_10_MotionMagic, 10, 10);

  // Set peak outputs
  srxClimberLeft->ConfigPeakOutputForward(0.6, 0);
  srxClimberLeft->ConfigPeakOutputReverse(-0.6, 0);

  // Set motion magic gains **These numbers aren't set right yet (for muck)**
  srxClimberLeft->SelectProfileSlot(0, 0);
  srxClimberLeft->Config_kF(0, 50, 0);
  srxClimberLeft->Config_kP(0, 2.5, 0);
  srxClimberLeft->Config_kI(0, 0.0015, 0);
  srxClimberLeft->Config_kD(0, 0, 0);

  // Set acceleration and cruise velocity
  srxClimberLeft->ConfigMotionCruiseVelocity(2500, 0);
  srxClimberLeft->ConfigMotionAcceleration(2000, 0);
}

int SubClimber::getEncoder()
{
  return srxClimberLeft->GetSelectedSensorPosition(0);
}

double SubClimber::getPos()
{
  _pos = getEncoder();

  frc::SmartDashboard::PutNumber("Raw relative encoder sensor units", _pos);

  _dist = SensorUnitsToMetres(_pos);

  frc::SmartDashboard::PutNumber("Actual Climber Position", _dist);

  return _dist;
}

void SubClimber::setSpeed(double speed) //Hardcodes power as %!!!!!
{
  //srxClimberLeft->Set(speed);
}

void SubClimber::SetPosition(double position)
{
  _targetPosition = position;
  std::cout << "angle input(degrees): " << position << std::endl;
  position = MetresToSensorUnits(position);
  std::cout << "angle input(ticks): " << position << std::endl;
  //srxClimberLeft->Set(ControlMode::MotionMagic, position);
}

double SubClimber::MetresToSensorUnits(double metres)
{
  return ((metres / _ticksPerMetre) * 4096);
}

double SubClimber::SensorUnitsToMetres(double sensorUnits)
{
  return (sensorUnits / 4096) * _ticksPerMetre;
}

bool SubClimber::IsOnTarget()
{
  if (_targetPosition == getPos())
  {
    return true;
  }
  else
  {
    return false;
  }
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
