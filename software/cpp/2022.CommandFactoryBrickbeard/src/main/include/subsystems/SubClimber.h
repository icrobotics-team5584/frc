#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/DoubleSolenoid.h>
#include <frc/DigitalInput.h>
#include <frc/simulation/DIOSim.h>
#include <frc/simulation/ElevatorSim.h>

#include "utilities/ICSparkMax.h"
#include "Constants.h"

class SubClimber : public frc2::SubsystemBase {
 public:
  static SubClimber& GetInstance() {
    static SubClimber inst;
    return inst;
  }

  void Periodic() override;
  void SimulationPeriodic() override;
  void ManualDrive(double speed);         // Move arms with percentage control
  void DriveTo(units::meter_t position);  // Move arms to a position (rotations)
  void Rotate();                          // Rotate arms out
  void Stow();                            // Rotate arms in
  bool GoingDown();                       // Check if arms target is below current pos
  bool GoingUp();                         // Check if arms target is above current position
  bool IsAtTargetPosition();              // check if both elevators have reached the target
  bool AtLowerLeftLimit() { return _lowerLeftLimit.Get(); }    // Check if left limit is hit
  bool AtLowerRightLimit() { return _lowerRightLimit.Get(); }  // Check if right limit is hit
  bool AtUpperLeftLimit() { return _upperLeftLimit.Get(); }    // check is left upper limit is hit
  bool AtUpperRightLimit() { return _upperRightLimit.Get(); }  // check is right upper limit is hit

  static constexpr units::meter_t NEAR_MAX_HEIGHT = 1.9_m;
  static constexpr units::meter_t NEAR_MIN_HEIGHT = 0.1_m;
  static constexpr units::meter_t MIN_HEIGHT = 0_m;
  static constexpr units::meter_t MAX_HEIGHT = 2_m;

 private:
  SubClimber();
  void StopMotorsFromHittingEnds();

  // Constants
  static constexpr double GEARING = 30.0;
  static constexpr units::meter_t PULLY_RADIUS = 2_in;
  static constexpr units::kilogram_t CARRIAGE_MASS = 0.1_kg;
  static constexpr double P = 0.1, I = 0, D = 0, F = 12.0;
  static constexpr units::meters_per_second_t MAX_VEL = 0.7_mps;
  static constexpr units::meters_per_second_squared_t MAX_ACCEL = 1_mps_sq;
  static constexpr units::meter_t TOLERANCE = 2_cm;
  static constexpr double POS_CONVERSION = 1 / GEARING * PULLY_RADIUS.value();

  // Eletronic Components
  // give the ICSparkMaxes the meters units so we can give it targets in meters and get encoder 
  // readings in meters and meters per second. 
  // This would have been rotations and rotations per min by default
  ICSparkMax<units::meter> _leftMotor{canid::climberLeft};
  ICSparkMax<units::meter> _rightMotor{canid::climberRight};

  frc::DoubleSolenoid _tilterPiston{1, frc::PneumaticsModuleType::CTREPCM,
                                    pcm::climberTilterForward, pcm::climberTilterReverse};

  frc::DigitalInput _lowerLeftLimit{dio::climberLeftLowerLimit};
  frc::DigitalInput _lowerRightLimit{dio::climberRightLowerLimit};
  frc::DigitalInput _upperLeftLimit{dio::climberLeftUpperLimit};
  frc::DigitalInput _upperRightLimit{dio::climberRightUpperLimit};

  // Simulation
  frc::sim::DIOSim _lowerLeftLimitSim{_lowerLeftLimit};
  frc::sim::DIOSim _lowerRightLimitSim{_lowerRightLimit};
  frc::sim::DIOSim _upperLeftLimitSim{_upperLeftLimit};
  frc::sim::DIOSim _upperRightLimitSim{_upperRightLimit};

  frc::sim::ElevatorSim _leftElevatorSim{
      frc::DCMotor::NEO(),
      GEARING,
      CARRIAGE_MASS,
      PULLY_RADIUS,
      MIN_HEIGHT,
      MAX_HEIGHT,
      false  // don't simulate gravity, we have springs
  };
  frc::sim::ElevatorSim _rightElevatorSim{_leftElevatorSim};  // copies the left one
};
