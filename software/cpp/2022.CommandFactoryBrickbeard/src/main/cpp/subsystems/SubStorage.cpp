#include "subsystems/SubStorage.h"
#include <frc/smartdashboard/SmartDashboard.h>

SubStorage::SubStorage() {
  frc::SmartDashboard::PutData("storage/motor", (wpi::Sendable*)&_motor);
  frc::SmartDashboard::PutData("storage/piston", (wpi::Sendable*)&_releasePiston);
  BlockBall();
};

void SubStorage::Periodic() {}

void SubStorage::Start() {
  _motor.Set(1);
}

void SubStorage::Stop() {
  _motor.Set(0);
}

void SubStorage::ReleaseBall() {
  _releasePiston.Set(frc::DoubleSolenoid::kReverse);
}

void SubStorage::BlockBall() {
  _releasePiston.Set(frc::DoubleSolenoid::kForward);
}