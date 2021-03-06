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
  LimitClimbUp.reset(new frc::DigitalInput(dio_ElevatorTop));
  LimitClimbDown.reset(new frc::DigitalInput(dio_ElevatorBottom));

  if(!LimitClimbDown->Get()){
    srxClimberLeft->SetSelectedSensorPosition(0.0);
    startedDown = true;
  } else {
    startedDown = false;
  }
  frc::SmartDashboard::PutBoolean("Correct Elevator Start", startedDown);

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
  frc::SmartDashboard::PutNumber("kP", kP);

  frc::SmartDashboard::PutNumber("Buddy Target", buddyTarget);
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
  //maxUpSpeed = frc::SmartDashboard::GetNumber("Elevator Up Speed", 0.8);
  //maxDownSpeed = frc::SmartDashboard::GetNumber("Elevator Down Speed", 0.45);
  //target = frc::SmartDashboard::GetNumber("Target ele", 0);
  frc::SmartDashboard::PutNumber("Target ele", target);
  kP = frc::SmartDashboard::GetNumber("kP", -0.0008);
  frc::SmartDashboard::PutNumber("elevator current speed", srxClimberLeft->GetMotorOutputPercent());
  frc::SmartDashboard::PutNumber("elevator position", srxClimberLeft->GetSelectedSensorPosition());

  buddyTarget = frc::SmartDashboard::GetNumber("Buddy Target", 3634);

  std::cout << "Elevator Encoder Position: " << srxClimberLeft->GetSelectedSensorPosition() << std::endl;

  frc::SmartDashboard::PutBoolean("limit top", LimitClimbUp->Get());
  frc::SmartDashboard::PutBoolean("limit bottom", LimitClimbDown->Get());
  frc::SmartDashboard::PutBoolean("PID enabled", PIDEnabled);

}

void SubClimber::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
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

void SubClimber::Up()
{
  PIDEnabled = false;
  RatchetsDisengage();
  setSpeed(_upSpeed);
}

void SubClimber::setSpeed(double speed) //Hardcodes power as %!!!!!
{

// dont move down when at bottom limit
  if (!LimitClimbDown->Get() && speed < 0) { // Inverted limit as required. (Elevator=Down.)
    speed = 0;
  }

// dont move up when at bottom limit
  if (!LimitClimbUp->Get() && speed > 0) { // Inverted limit as required. (Elevator=Up.)
    speed = 0;
  }

  if(startedDown){
    if (speed >= 0 && isElevatorLocked){
      std::cout << "elevator stop" << std::endl;
      srxClimberLeft->Set(0);
    } else {
      srxClimberLeft->Set(-speed);
    }
  } else {
    srxClimberLeft->Set(0);
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
  
  if(!LimitClimbDown->Get() && target < srxClimberLeft->GetSelectedSensorPosition()){
    srxClimberLeft->SetSelectedSensorPosition(0.0);
    target = 0;
  }

  if(!LimitClimbUp->Get() && target > srxClimberLeft->GetSelectedSensorPosition()){
    srxClimberLeft->SetSelectedSensorPosition(elevatorUpPos);
    target = elevatorUpPos;
  }
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
  if(PIDEnabled){
    setSpeed(PIDOutput);
  } else {
    setSpeed(0);
  }
  lastError = error;
  
}

void SubClimber::ElevatorExtendMax(){
  target = elevatorUpPos;
}

void SubClimber::ElevaterExtendMin(){
  target = 0;
}

void SubClimber::ElevatorExtendBuddy(){

  if(srxClimberLeft->GetSelectedSensorPosition() > buddyTarget){
    target = buddyTarget;
  }
}

void SubClimber::EnablePID(){
  PIDEnabled = true;
}

void SubClimber::DisablePID(){
  PIDEnabled = false;
}

bool SubClimber::IsAtTarget(){
  if(srxClimberLeft->GetSelectedSensorPosition() < target + 500 && srxClimberLeft->GetSelectedSensorPosition() > target - 500){
    return true;
  } else {
    return false;
  }
}