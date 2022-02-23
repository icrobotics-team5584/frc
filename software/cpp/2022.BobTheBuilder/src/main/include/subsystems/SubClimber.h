#pragma once

#include <frc/DigitalInput.h>
#include <frc/DoubleSolenoid.h>
#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>

#include <vector>

#include "Constants.h"

class SubClimber : public frc2::SubsystemBase {
 public:
  enum State {
    STOWED_FULL_RETRACTED,
    STOWED_NEAR_RETRACTED,
    STOWED_FULL_EXTENDED,
    STOWED_NEAR_EXTENDED,
    ROTATED_FULL_RETRACTED,
    ROTATED_NEAR_RETRACTED,
    ROTATED_FULL_EXTENDED,
    ROTATED_NEAR_EXTENDED
  };

  SubClimber();
  void Periodic() override;        // Called every 20ms
  void ManualDrive(double speed);  // Move arms with percentage control
  void DriveTo(double position);   // Move arms to a position (rotations)
  void Extend();                   // Extend arms to top
  void Retract();                  // Retract arms to bottom
  void Rotate();                   // Rotate arms out
  void Stow();                     // Rotate arms in
  void Lock();                     // Extend locking pistons
  void Unlock();                   // Retract locking pistons
  void SetDesiredState(State state); // Choose arms position and rotation
  void StepClimbSequence();        // Transition along the climb sequence
  void ResetClimbSequence();       // Reset climb sequence to beginning
  void SetEncoders(double value);  // Set encoder values
  bool AtLeftLimit();              // Check if left limit is hit
  bool AtRightLimit();             // Check if right limit is hit
  bool IsLocked();                 // Check if locking pistons are extended
  bool GoingDown();                // Check if arms target is below current pos

 private:
  static constexpr double kP = 5e-5, kI = 1e-6, kD = 0, KIz = 0, kFF = 0,
                          kMaxOutPut = 1, kMinOutput = -1, kMaxVel = 6000,
                          kMinVel = 0, kMaxAcc = 6000, kAllErr = 0;

  int _targetPosition = 0;
  bool _inSmartMotionMode = false;
  static constexpr double MIN_POSITION = 0;
  static constexpr double MAX_POSITION = 100;
  static constexpr double NEAR_MAX_POS = 90;
  static constexpr double NEAR_MIN_POS = 10;
  static constexpr double SAFETY_FACTOR = 10;

  rev::CANSparkMax _spmLeftElevator{can::spmLeftClimber,
                                    rev::CANSparkMax::MotorType::kBrushless};

  rev::CANSparkMax _spmRightElevator{can::spmRightClimber,
                                     rev::CANSparkMax::MotorType::kBrushless};

  frc::DoubleSolenoid _solTilter{1, frc::PneumaticsModuleType::CTREPCM,
                                 pcm::solClimbTilterForward,
                                 pcm::solClimbTilterReverse};

  frc::DoubleSolenoid _solLock{0, frc::PneumaticsModuleType::CTREPCM,
                               pcm2::solClimbLockForward,
                               pcm2::solClimbLockReverse};

  frc::DigitalInput _lmtLeft{dio::lmtClimberLeft};
  frc::DigitalInput _lmtRight{dio::lmtClimberRight};

  rev::SparkMaxRelativeEncoder _encLeftElevator{_spmLeftElevator.GetEncoder()};
  rev::SparkMaxRelativeEncoder _encRightElevator{
      _spmRightElevator.GetEncoder()};

  rev::SparkMaxPIDController _pidLeftMotorController =
      _spmLeftElevator.GetPIDController();
  rev::SparkMaxPIDController _pidRightMotorController =
      _spmRightElevator.GetPIDController();

  std::vector<State> climbSequence = {
      // mid bar
      STOWED_FULL_RETRACTED, STOWED_NEAR_EXTENDED, STOWED_FULL_RETRACTED,
      // high bar
      STOWED_NEAR_RETRACTED, ROTATED_NEAR_RETRACTED, ROTATED_FULL_EXTENDED,
      STOWED_FULL_EXTENDED, STOWED_FULL_RETRACTED,
      // transverse bar
      STOWED_NEAR_RETRACTED, ROTATED_NEAR_RETRACTED, ROTATED_FULL_EXTENDED,
      STOWED_FULL_EXTENDED, STOWED_FULL_RETRACTED};

  std::vector<State>::iterator currentStep = climbSequence.begin();
};
