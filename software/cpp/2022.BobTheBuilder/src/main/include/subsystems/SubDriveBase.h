// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <rev/CANSparkMax.h>
#include <frc/Encoder.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/geometry/Pose2d.h>
#include <frc/kinematics/DifferentialDriveOdometry.h>
#include <frc/motorcontrol/MotorControllerGroup.h>
#include <frc/motorcontrol/PWMSparkMax.h>
#include <frc2/command/SubsystemBase.h>
#include <units/voltage.h>
#include <AHRS.h>
#include <frc/smartdashboard/Field2d.h>
#include <frc/Timer.h>

#include "Constants.h"

class SubDriveBase : public frc2::SubsystemBase {
 public:
  // squaredInputs: 
  // If set, overrides constant-curvature turning for turn-in-place maneuvers. zRotation will control turning rate instead of curvature.
  SubDriveBase();

  void drive(double speed, double rotation, bool squaredInputs = false);

  // Create instances of motor controllers
  rev::CANSparkMax _spmFrontLeft{can::spmDriveBaseFrontLeft, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax _spmFrontRight{can::spmDriveBaseFrontRight, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax _spmBackLeft{can::spmDriveBaseBackLeft, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax _spmBackRight{can::spmDriveBaseBackRight, rev::CANSparkMax::MotorType::kBrushless};
  frc::DifferentialDrive _diffDrive{_spmFrontLeft, _spmFrontRight};

  void Periodic() override;

    /**
   * Returns the current wheel speeds of the robot.
   *
   * @return The current wheel speeds.
   */
  frc::DifferentialDriveWheelSpeeds GetWheelSpeeds();

    /**
   * Resets the odometry to the specified pose.
   *
   * @param pose The pose to which to set the odometry.
   */
  void ResetOdometry(frc::Pose2d pose);

    /**
   * Controls each side of the drive directly with a voltage.
   *
   * @param left the commanded left output
   * @param right the commanded right output
   */
  void TankDriveVolts(units::volt_t left, units::volt_t right);

  /**
   * Resets the drive encoders to currently read a position of 0.
   */
  void ResetEncoders();

  /**
   * Gets the average distance of the TWO encoders.
   *
   * @return the average of the TWO encoder readings
   */
  double GetAverageEncoderDistance();

  /**
   * Gets the left drive encoder.
   *
   * @return the left drive encoder
   */
  rev::RelativeEncoder& GetLeftEncoder();

  /**
   * Gets the right drive encoder.
   *
   * @return the right drive encoder
   */
  rev::RelativeEncoder& GetRightEncoder();

  /**
   * Sets the max output of the drive.  Useful for scaling the drive to drive
   * more slowly.
   *
   * @param maxOutput the maximum output to which the drive will be constrained
   */
  void SetMaxOutput(double maxOutput);

  /**
   * Returns the heading of the robot.
   *
   * @return the robot's heading in degrees, from -180 to 180
   */
  float GetHeading();

  /**
   * Returns the turn rate of the robot.
   *
   * @return The turn rate of the robot, in degrees per second
   */
  double GetTurnRate();

  /**
   * Returns the currently-estimated pose of the robot.
   *
   * @return The pose.
   */
  frc::Pose2d GetPose();

  void resetYaw();

  bool isNavxCal();

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.

  // Encoder for autonomous drive
  rev::SparkMaxRelativeEncoder _leftEncoder{_spmFrontLeft.GetEncoder()}; 
  rev::SparkMaxRelativeEncoder _rightEncoder{_spmFrontRight.GetEncoder()};

  // The gyro sensor
  AHRS _gyro{frc::SerialPort::kMXP};
  frc::DifferentialDriveOdometry _odometry{_gyro.GetRotation2d()};

  frc::Field2d _fieldSim;

  double encoderPos = 0;
  double time = 0;
  frc::Timer timer;
};
