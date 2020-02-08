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
  solClimberRatchets.reset(new frc::DoubleSolenoid(pcm_1, pcm_solRatchetEngage, pcm_solRatchetDisengage));
  LimitClimbUp.reset(new frc::DigitalInput(0));
  LimitClimbDown.reset(new frc::DigitalInput(1));

  srxClimberLeft->SetSelectedSensorPosition(0.0);
  srxClimberLeft->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative);

  srxClimberLeft->ConfigFactoryDefault();
  srxClimberRight->ConfigFactoryDefault();
  srxClimberLeft->SetSensorPhase(false);
  srxClimberRight->Set(ControlMode::Follower, can_srxClimberLeft);
  
  srxClimberRight->SetInverted(true);
  srxClimberLeft->SetInverted(false);

  srxClimberLeft->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Absolute);

  frc::SmartDashboard::PutNumber("Elevator Up Speed", maxUpSpeed);
  frc::SmartDashboard::PutNumber("Elevator Down Speed", maxDownSpeed);
  frc::SmartDashboard::PutNumber("Target ele", target);
  frc::SmartDashboard::PutNumber("kP", kP);


}

void SubClimber::Periodic(){
  //frc::SmartDashboard::PutBoolean("Limit switch DOWN", LimitClimbDownGet());
  //frc::SmartDashboard::PutBoolean("Limit switch UP", LimitClimbUpGet());
  _upSpeed = frc::SmartDashboard::GetNumber("Climber Speed", _upSpeed);
  frc::SmartDashboard::PutNumber("Climber Speed", _upSpeed);
  if(timer.Get() > 0.5){
    isElevatorLocked = false;
  }
  frc::SmartDashboard::PutBoolean("ratchet not engaged", !isElevatorLocked);
  CustomPID(srxClimberLeft->GetSelectedSensorPosition());
  maxUpSpeed = frc::SmartDashboard::GetNumber("Elevator Up Speed", 0.8);
  maxDownSpeed = frc::SmartDashboard::GetNumber("Elevator Down Speed", 0.45);
  //target = frc::SmartDashboard::GetNumber("Target ele", 0);
  kP = frc::SmartDashboard::GetNumber("kP", -0.0008);
  frc::SmartDashboard::PutNumber("elevater current speed", srxClimberLeft->GetMotorOutputPercent());
  frc::SmartDashboard::PutNumber("elevater position", srxClimberLeft->GetSelectedSensorPosition());
}

void SubClimber::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

void SubClimber::MoveUp(){
// if(!isElevatorLocked){
//   srxClimberLeft->Set(-_upSpeed);
// } else {
//   srxClimberLeft->Set(0);
// }
}

void SubClimber::MoveDown(){
  //srxClimberLeft->Set(_downSpeed);
}

void SubClimber::Stop(){
  srxClimberLeft->Set(0);
}

void SubClimber::RatchetsDisengage(){
  timer.Reset();
  timer.Start();
  std::cout << "ratchet disengage" << std::endl;
  solClimberRatchets->Set(frc::DoubleSolenoid::kForward);
}

void SubClimber::RatchetsEngage(){
  timer.Stop();
  timer.Reset();
  isElevatorLocked = true;
  std::cout << "ratchet engage" << std::endl;
  solClimberRatchets->Set(frc::DoubleSolenoid::kReverse);
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
  if (-speed > 0 && isElevatorLocked){
    srxClimberLeft->Set(0);
  } else {
    srxClimberLeft->Set(-speed);
  }
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

void SubClimber::CustomPID(double PIDIntput){
  error = PIDIntput - target;
  intergral = intergral + error;
  derivative = error - lastError;
  PIDOutput = (error * kP) + (intergral * kI) + (derivative * kD);
  if (PIDOutput > maxUpSpeed){
    PIDOutput = maxUpSpeed;
  }
  if (PIDOutput < maxDownSpeed){
    PIDOutput = maxDownSpeed;
  }
  setSpeed(PIDOutput);
  lastError = error;
  
}

void SubClimber::ElevatorExtendMax(){
  target = 30900;
}

void SubClimber::ElevaterExtendMin(){
  target = 0;
}