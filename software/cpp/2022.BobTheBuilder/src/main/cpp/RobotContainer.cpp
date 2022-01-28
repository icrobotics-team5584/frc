// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <utility>

#include <frc/controller/PIDController.h>
#include <frc/controller/RamseteController.h>
#include <frc/shuffleboard/Shuffleboard.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/trajectory/constraint/DifferentialDriveVoltageConstraint.h>
#include <frc2/command/InstantCommand.h>
#include <frc2/command/RamseteCommand.h>
#include <frc2/command/SequentialCommandGroup.h>
#include <frc2/command/button/JoystickButton.h>


#include "RobotContainer.h"

RobotContainer::RobotContainer() {
  _subDriveBase.SetDefaultCommand(CmdJoystickDrive(&_subDriveBase, &_joystick0));
  // Configure the button bindings
  ConfigureButtonBindings();
  frc::SmartDashboard::PutNumber("Kp velocity", DriveConstants::kPDriveVel);
}

void RobotContainer::ConfigureButtonBindings() {
  
}


frc2::Command* RobotContainer::GetAutonomousCommand() {
  // Create a voltage constraint to ensure we don't accelerate too fast
  frc::DifferentialDriveVoltageConstraint autoVoltageConstraint(
      frc::SimpleMotorFeedforward<units::meters>(
          DriveConstants::ks, DriveConstants::kv, DriveConstants::ka),
      kDriveKinematics, 10_V);

  // Set up config for trajectory
  frc::TrajectoryConfig config(AutoConstants::kMaxSpeed,
                               AutoConstants::kMaxAcceleration);
  // Add kinematics to ensure max speed is actually obeyed
  config.SetKinematics(kDriveKinematics);
  // Apply the voltage constraint
  config.AddConstraint(autoVoltageConstraint);

  // An example trajectory to follow.  All units in meters.
  auto exampleTrajectory = frc::TrajectoryGenerator::GenerateTrajectory(
      // Start at the origin facing the +X direction
      frc::Pose2d(0_m, 0_m, frc::Rotation2d(0_deg)),
      // Pass through these two interior waypoints, making an 's' curve path
      {frc::Translation2d(1_m, 0_m)},
      // End 3 meters straight ahead of where we started, facing forward
      frc::Pose2d(1_m, 0_m, frc::Rotation2d(0_deg)),
      // Pass the config
      config);
    
    fs::path deployDirectory = frc::filesystem::GetDeployDirectory();
    deployDirectory = deployDirectory / "Paths" / "MoveForward.wpilib.json";
    trajectory = frc::TrajectoryUtil::FromPathweaverJson(deployDirectory.string());

  frc2::RamseteCommand ramseteCommand(
      trajectory, [this]() { return _subDriveBase.GetPose(); },
      frc::RamseteController(AutoConstants::kRamseteB,
                             AutoConstants::kRamseteZeta),
      frc::SimpleMotorFeedforward<units::meters>(
          DriveConstants::ks, DriveConstants::kv, DriveConstants::ka),
      kDriveKinematics,
      [this] { return _subDriveBase.GetWheelSpeeds(); },
      frc2::PIDController(frc::SmartDashboard::GetNumber("Kp velocity", 0), 0, 0),
      frc2::PIDController(frc::SmartDashboard::GetNumber("Kp velocity", 0), 0, 0),
      [this](auto left, auto right) { _subDriveBase.TankDriveVolts(left, right); },
      {&_subDriveBase});

  // Reset odometry to the starting pose of the trajectory.
  _subDriveBase.ResetOdometry(trajectory.InitialPose());

  return new frc2::SequentialCommandGroup(
      std::move(ramseteCommand),
      frc2::InstantCommand([this] { _subDriveBase.TankDriveVolts(0_V, 0_V); }, {}));
}
