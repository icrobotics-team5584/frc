#pragma once

#include <frc/DigitalInput.h>
#include <frc/DoubleSolenoid.h>
#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>
#include <tuple>

#include <vector>

#include "Constants.h"

class SubClimber : public frc2::SubsystemBase {
 public:
  // enum State {
  //   STOWED_FULL_RETRACTED,
  //   STOWED_NEAR_RETRACTED,
  //   STOWED_FULL_EXTENDED,
  //   STOWED_NEAR_EXTENDED,
  //   ROTATED_FULL_RETRACTED,
  //   ROTATED_NEAR_RETRACTED,
  //   ROTATED_FULL_EXTENDED,
  //   ROTATED_NEAR_EXTENDED
  // };

  enum SpeedState {
    FAST, SLOW
  };

  enum TiltState {
    ROTATED, STOWED
  };

  enum ElevatorState {
    FULL_RETRACTED, NEAR_RETRACTED, FULL_EXTENDED, NEAR_EXTENDED
  };

  struct ClimberState {
    TiltState tilt;
    ElevatorState elevator;
    SpeedState speed;
  };

  SubClimber();
  void Periodic() override;        // Called every 20ms
  void ManualDrive(double speed);  // Move arms with percentage control
  void DriveTo(double position);   // Move arms to a position (rotations)
  void Extend();                   // Extend arms to top
  void Retract();                  // Retract arms to bottom
  void Rotate();                   // Rotate arms out
  void Stow();                     // Rotate arms in
  void SetDesiredState(ClimberState state); // Choose arms position and rotation
  void StepClimbSequence();        // Transition along the climb sequence
  void ResetClimbSequence();       // Reset climb sequence to beginning
  void SetEncoders(double value);  // Set encoder values
  bool AtLeftLimit();              // Check if left limit is hit
  bool AtRightLimit();             // Check if right limit is hit
  bool GoingDown();                // Check if arms target is below current pos

 private:
  static constexpr double kP = 5e-5, kI = 1e-6, kD = 0, KIz = 0, kFF = 0,
                          kMaxOutPut = 1, kMinOutput = -1, kFastMaxVel = 6000,
                          kSlowMaxVel = 3000, kMinVel = 0, kMaxAcc = 6000,
                          kAllErr = 0;

  int _targetPosition = 0;
  bool _inSmartMotionMode = false;
  static constexpr double MIN_POSITION = 0;
  static constexpr double MAX_POSITION = 160;
  static constexpr double NEAR_MAX_POS = 107;
  static constexpr double NEAR_MIN_POS = 20;
  static constexpr double SAFETY_FACTOR = 0;

  rev::CANSparkMax _spmLeftElevator{can::spmLeftClimber,
                                    rev::CANSparkMax::MotorType::kBrushless};

  rev::CANSparkMax _spmRightElevator{can::spmRightClimber,
                                     rev::CANSparkMax::MotorType::kBrushless};

  frc::DoubleSolenoid _solTilter{1, frc::PneumaticsModuleType::CTREPCM,
                                 pcm::solClimbTilterForward,
                                 pcm::solClimbTilterReverse};

  frc::DigitalInput _lmtLeft{dio::lmtClimberLeft};
  frc::DigitalInput _lmtRight{dio::lmtClimberRight};

  rev::SparkMaxRelativeEncoder _encLeftElevator{_spmLeftElevator.GetEncoder()};
  rev::SparkMaxRelativeEncoder _encRightElevator{
      _spmRightElevator.GetEncoder()};

  rev::SparkMaxPIDController _pidLeftMotorController =
      _spmLeftElevator.GetPIDController();
  rev::SparkMaxPIDController _pidRightMotorController =
      _spmRightElevator.GetPIDController();

  std::vector<ClimberState> climbSequence = {
    // mid bar
    {STOWED, FULL_RETRACTED, SLOW}, {STOWED, NEAR_EXTENDED, SLOW}, 
    {STOWED, FULL_RETRACTED, SLOW},
    // high bar
    {STOWED, NEAR_RETRACTED, SLOW}, {ROTATED, NEAR_RETRACTED, SLOW}, 
    {ROTATED, FULL_EXTENDED, SLOW}, {STOWED, FULL_EXTENDED, SLOW}, 
    {STOWED, FULL_RETRACTED, SLOW},
    // transverse bar
    {STOWED, NEAR_RETRACTED, SLOW}, {ROTATED, NEAR_RETRACTED, SLOW}, 
    {ROTATED, FULL_EXTENDED, SLOW}, {STOWED, FULL_EXTENDED, SLOW}, 
    {STOWED, FULL_RETRACTED, SLOW}
  };
  
  //     // mid bar
  //     STOWED_FULL_RETRACTED, STOWED_NEAR_EXTENDED, STOWED_FULL_RETRACTED,
  //     // high bar
  //     STOWED_NEAR_RETRACTED, ROTATED_NEAR_RETRACTED, ROTATED_FULL_EXTENDED,
  //     STOWED_FULL_EXTENDED, STOWED_FULL_RETRACTED,
  //     // transverse bar
  //     STOWED_NEAR_RETRACTED, ROTATED_NEAR_RETRACTED, ROTATED_FULL_EXTENDED,
  //     STOWED_FULL_EXTENDED, STOWED_FULL_RETRACTED};

  std::vector<ClimberState>::iterator currentStep = climbSequence.begin();
};
