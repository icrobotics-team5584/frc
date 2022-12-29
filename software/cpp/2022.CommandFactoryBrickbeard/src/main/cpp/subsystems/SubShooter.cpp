#include "subsystems/SubShooter.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <units/angle.h>
#include <units/angular_velocity.h>
#include <frc2/command/Command.h>

SubShooter::SubShooter() {
  _motorA.SetPIDFF(P, I, D, F);
  _motorB.Follow(_motorA);
  frc::SmartDashboard::PutData("shooter/motor", (wpi::Sendable*)&_motorA);

  // Setup shooter speed table
  _speedTable.insert(1_m, 2000_rpm); // When we are 1m from goal, spin flywheel at 2000 rpm
  _speedTable.insert(2_m, 2200_rpm); // When we are 2m from goal, spin flywheel at 2200 rpm
  _speedTable.insert(3_m, 2400_rpm); // etc...
  _speedTable.insert(4_m, 2600_rpm); // You can grab an intermediary distance from this table and 
  _speedTable.insert(5_m, 2800_rpm); // it will give you an interpolated speed.
  _speedTable.insert(6_m, 3000_rpm);
};

void SubShooter::Periodic() {}

void SubShooter::AccelerateFlywheel(units::meter_t dist) {
  _motorA.SetVelocityTarget(_speedTable[dist]);
}

bool SubShooter::AtTargetVelocity() {
  return _motorA.GetVelError() < 20_rpm;
}

void SubShooter::SimulationPeriodic() {
  _flywheelSim.SetInputVoltage(_motorA.GetSimVoltage());
  _flywheelSim.Update(20_ms);
  auto vel = _flywheelSim.GetAngularVelocity();
  _motorA.UpdateSimEncoder(0_tr /*ignore pos, don't need it for flywheels*/, vel);
}