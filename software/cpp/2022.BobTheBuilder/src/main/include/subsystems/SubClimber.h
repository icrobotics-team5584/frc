#pragma once

#include <frc/DigitalInput.h>
#include <frc/DoubleSolenoid.h>
#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>
#include <tuple>
#include <math.h>

#include <vector>

#include "Constants.h"

#include <frc/simulation/ElevatorSim.h>
#include <frc/smartdashboard/Mechanism2d.h>
#include <frc/smartdashboard/MechanismLigament2d.h>
#include <frc/smartdashboard/MechanismRoot2d.h>
#include <frc/simulation/DIOSim.h>


class SubClimber : public frc2::SubsystemBase {
 public:
  

  


  SubClimber();
  void Periodic() override;        // Called every 20ms
  void SimulationPeriodic() override;
  void ManualDrive(double speed);  // Move arms with percentage control
  void DriveTo(double position);   // Move arms to a position (rotations)
  void Extend();                   // Extend arms to top
  void Retract();                  // Retract arms to bottom
  void Rotate();                   // Rotate arms out
  void Stow();                     // Rotate arms in
  void SetEncoders(double value);  // Set encoder values
  void SetMaxSpeed();              // Set Climber max speed
  void SetMinSpeed();              // Set Climber min speed
  bool AtLeftLimit();              // Check if left limit is hit
  bool AtRightLimit();             // Check if right limit is hit
  bool GoingDown();                // Check if arms target is below current pos
  bool IsAtTargetPosition();       // check if both elevators have reached the target

  static constexpr double MIN_POSITION = 0;
  static constexpr double MAX_POSITION = 165;
  static constexpr double NEAR_MAX_POS = 130;
  static constexpr double NEAR_MIN_POS = 40;
  static constexpr double SAFETY_FACTOR = 0;
  static constexpr double BELOW_MIN = -10;
  

 private:
  static constexpr double kP = 5e-5, kI = 1e-6, kD = 0, KIz = 0, kFF = 0,
                          kMaxOutPut = 1, kMinOutput = -1, kFastMaxVel = 6000,
                          kSlowMaxVel = 3000, kMinVel = 0, kMaxAcc = 6000,
                          kAllErr = 0.5;

  int _targetPosition = 0;
  bool _inSmartMotionMode = false;
  

  rev::CANSparkMax _spmLeftElevator{can::spmLeftClimber,
                                    rev::CANSparkMax::MotorType::kBrushless};

  rev::CANSparkMax _spmRightElevator{can::spmRightClimber,
                                     rev::CANSparkMax::MotorType::kBrushless};

  frc::DoubleSolenoid _solTilter{1, frc::PneumaticsModuleType::CTREPCM,
                                 pcm::solClimberForward,
                                 pcm::solClimberReverse};

  frc::DigitalInput _lmtLeft{dio::lmtClimberLeft};
  frc::DigitalInput _lmtRight{dio::lmtClimberRight};

  rev::SparkMaxRelativeEncoder _encLeftElevator{_spmLeftElevator.GetEncoder()};
  rev::SparkMaxRelativeEncoder _encRightElevator{
      _spmRightElevator.GetEncoder()};

  rev::SparkMaxPIDController _pidLeftMotorController =
      _spmLeftElevator.GetPIDController();
  rev::SparkMaxPIDController _pidRightMotorController =
      _spmRightElevator.GetPIDController();

    //simulation
    static constexpr double kElevatorGearing = 30.0;
    static constexpr units::meter_t kElevatorDrumRadius = 2_in;
    static constexpr units::kilogram_t kCarriageMass = 0.1_kg;

    static constexpr units::meter_t kMinElevatorHeight = 0_m;
    static constexpr units::meter_t kMaxElevatorHeight = 2_m;
    frc::DCMotor m_elevatorGearbox = frc::DCMotor::NEO();
    
    frc::sim::DIOSim _leftLimitSim{_lmtLeft};   
    frc::sim::DIOSim _rightLimitSim{_lmtRight};

    frc::sim::ElevatorSim _leftElevatorSim{m_elevatorGearbox,
                                      kElevatorGearing,
                                      kCarriageMass,
                                      kElevatorDrumRadius,
                                      kMinElevatorHeight,
                                      kMaxElevatorHeight};
    frc::sim::ElevatorSim _rightElevatorSim{m_elevatorGearbox,
                                      kElevatorGearing,
                                      kCarriageMass,
                                      kElevatorDrumRadius,
                                      kMinElevatorHeight,
                                      kMaxElevatorHeight};


    // Create a Mechanism2d display of an elevator
    frc::Mechanism2d _leftMech{0.1, kMaxElevatorHeight.value()};
    frc::MechanismRoot2d* _leftRoot =
        _leftMech.GetRoot("Left Elevator Root", 0.05, 0);
    frc::MechanismLigament2d* _leftLigament =
        _leftRoot->Append<frc::MechanismLigament2d>(
            "Left Elevator", _leftElevatorSim.GetPosition().value(), 90_deg);

    frc::Mechanism2d _rightMech{0.1, kMaxElevatorHeight.value()};
    frc::MechanismRoot2d* _rightRoot =
        _rightMech.GetRoot("Right Elevator Root", 0.05, 0);
    frc::MechanismLigament2d* _rightLigament =
        _rightRoot->Append<frc::MechanismLigament2d>(
            "Right Elevator", _rightElevatorSim.GetPosition().value(), 90_deg);
};
