/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include <frc/DigitalInput.h>
#include <frc/DoubleSolenoid.h>
#include <rev/CANSparkMax.h>
#include <networktables/NetworkTableEntry.h>
#include <String>


class SubStorage : public frc::Subsystem {
 private:
  const double kDefaultBottomRollerSpeed = 0.8;
  const double kDefaultBottomRollerReverseSpeed = -0.8;
  const double kDefaultFeederSpeed = 0.8;
  double _speed = kDefaultFeederSpeed;

  std::shared_ptr<TalonSRX> srxStorage;
  rev::CANSparkMax spmBottomRoller;

  frc::DigitalInput lbrTopStorage;
  std::shared_ptr<frc::DoubleSolenoid> solStorageActuator;

  std::shared_ptr<frc::DigitalInput> lbrBottom;
  std::shared_ptr<frc::DigitalInput> lbrTop;
  std::shared_ptr<frc::DigitalInput> lbrRoller;

  // Shuffleboard values
  const std::string kShuffleBoardSettingsTab = "Storage Settings";
  nt::NetworkTableEntry nteBottomRollerSpeed;
  nt::NetworkTableEntry nteBottomRollerReverseSpeed;

 public:
  SubStorage();
  void InitDefaultCommand() override;
  void Periodic() override;
  bool GetLbrTopStorage();
  void Forward();
  void Backward();
  void BottomRollerForward();
  void BottomRollerBackward();
  void BottomRollerStop();
  void Stop();

  bool lbrBottomIsBlocked();
  bool lbrTopIsBlocked();
  bool lbrRollerIsBlocked();


  void Expand();
  void Retract();
};
