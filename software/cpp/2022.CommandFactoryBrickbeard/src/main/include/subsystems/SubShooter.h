#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/simulation/FlywheelSim.h>
#include <frc/system/plant/DCMotor.h>
#include <wpi/interpolating_map.h>
#include <units/length.h>
#include <units/moment_of_inertia.h>

#include "utilities/ICSparkMax.h"
#include "Constants.h"

class SubShooter : public frc2::SubsystemBase {
 public:
  static SubShooter& GetInstance() {
    static SubShooter inst;
    return inst;
  }

  void Periodic() override;
  void SimulationPeriodic() override;
  void AccelerateFlywheel(units::meter_t dist);
  bool AtTargetVelocity();

 private:
  SubShooter();
  static constexpr double GEARING = 1;
  static constexpr units::kilogram_square_meter_t MOI = 0.005_kg_sq_m;
  wpi::interpolating_map<units::meter_t, units::turns_per_second_t> _speedTable;

  static constexpr double P = 0.5;
  static constexpr double I = 0.0;
  static constexpr double D = 0.1;
  static constexpr double F = 0.125;

  ICSparkMax<> _motorA{canid::shooterA};
  ICSparkMax<> _motorB{canid::shooterB};

  frc::sim::FlywheelSim _flywheelSim{frc::DCMotor::NEO(2), GEARING, MOI};
};
