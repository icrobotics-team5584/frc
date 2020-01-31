/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SubIntake.h"
#include "RobotMap.h"
#include <frc/smartdashboard/SmartDashboard.h>

SubIntake::SubIntake() : Subsystem("ExampleSubsystem") {
  srxIntake.reset(new TalonSRX(kIntakeMotor));
  solIntakeActuator.reset(new frc::DoubleSolenoid(pcm_solIntakeDeploy, pcm_solIntakeRetract));
  // Setup current limiting. 
  /* Notes on current limiting:
   * - Current must go above PeakCurrentLimit for a number of milliseconds equal to 
   *      PeakCurrentDuration, then current will be limited to ContinuousCurrentLimit.
   * - Setting a value to zero will instead set it to 1
   * - Values are in Amps and must be integers, not doubles
   * - Adding a 2 second ramp rate with talon->ConfigOpenLoopRamp(...) will make the current curve 
   *      look much more like what is expected. That is not used here though because it is desirable
   *      for an intake to speed up quickly. (So the graph on shuffleboard might look odd.)
   * - A timeout for sending these commands is an optional parameter, we did not use that
   * - This will limit the INPUT CURRENT into the Talon, not the output current to the motor
   * - Should always factory reset the talon settings first to avoid keeping old settings
   * - Some example current curves and values are on the IC Google Drive under 2020>Software
   */ 
  srxIntake->ConfigFactoryDefault();
  srxIntake->ConfigPeakCurrentLimit(0); //(current limit in amps(integer), timeout in milliseconds)
	srxIntake->ConfigPeakCurrentDuration(0); //(time over limit to trigger in milliseconds, timeout in milliseconds)
	srxIntake->ConfigContinuousCurrentLimit(1); //(amps(integer) to set current to, timeout in milliseconds)
	srxIntake->EnableCurrentLimit(false);

  frc::SmartDashboard::PutNumber("Intake Speed", kDefaultSpeed);
}

void SubIntake::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void SubIntake::Intake() {
  srxIntake->Set(ControlMode::PercentOutput, _speed);
}

void SubIntake::Outtake() {
  srxIntake->Set(ControlMode::PercentOutput, -_speed);
}

void SubIntake::Stop() {
  srxIntake->Set(ControlMode::PercentOutput, 0);
}

void SubIntake::Periodic() {
  // Update intake speed from dashboard
  frc::SmartDashboard::PutNumber("Intake Current", srxIntake->GetOutputCurrent());
  _speed = frc::SmartDashboard::GetNumber("Intake Speed", kDefaultSpeed);
}

void SubIntake::Deploy() {
  solIntakeActuator -> Set(frc::DoubleSolenoid::kReverse);
}

void SubIntake::Retract() {
  solIntakeActuator -> Set(frc::DoubleSolenoid::kForward);
}