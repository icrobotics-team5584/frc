#pragma once

#include <frc/DigitalInput.h>
#include <frc/DoubleSolenoid.h>
#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>
#include <tuple>
#include <math.h>

#include <vector>

#include "Constants.h"

class SubClimber : public frc2::SubsystemBase {
 public:
  

  


  SubClimber();
  void Periodic() override;        // Called every 20ms
  void ManualDrive(double speed);  // Move arms with percentage control
  void DriveTo(double position);   // Move arms to a position (rotations)
  void Extend();                   // Extend arms to top
  void Retract();                  // Retract arms to bottom
  void Rotate();                   // Rotate arms out
  void Stow();                     // Rotate arms in
  void SetEncoders(double value);  // Set encoder values
  bool AtLeftLimit();              // Check if left limit is hit
  bool AtRightLimit();             // Check if right limit is hit
  bool GoingDown();                // Check if arms target is below current pos
  bool IsAtTargetPosition();       // check if both elevators have reached the target

  static constexpr double MIN_POSITION = 0;
  static constexpr double MAX_POSITION = 160;
  static constexpr double NEAR_MAX_POS = 107;
  static constexpr double NEAR_MIN_POS = 20;
  static constexpr double SAFETY_FACTOR = 0;

 private:
  static constexpr double kP = 5e-5, kI = 1e-6, kD = 0, KIz = 0, kFF = 0,
                          kMaxOutPut = 1, kMinOutput = -1, kFastMaxVel = 6000,
                          kSlowMaxVel = 3000, kMinVel = 0, kMaxAcc = 6000,
                          kAllErr = 0;

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


  
};
