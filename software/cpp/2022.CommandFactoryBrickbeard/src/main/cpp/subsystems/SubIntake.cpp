#include "subsystems/SubIntake.h"
#include <frc/smartdashboard/SmartDashboard.h>

SubIntake::SubIntake(){
  frc::SmartDashboard::PutData("intake/motor", (wpi::Sendable*)&_motor);
  frc::SmartDashboard::PutData("intake/piston", (wpi::Sendable*)&_deployPiston);
};

void SubIntake::Periodic() {}

void SubIntake::Intake() {
  _motor.Set(1);
}

void SubIntake::Stop() {
  _motor.Set(0);
}

void SubIntake::Deploy() {
  _deployPiston.Set(frc::DoubleSolenoid::kForward);
}

void SubIntake::Retract() {
  _deployPiston.Set(frc::DoubleSolenoid::kReverse);
}