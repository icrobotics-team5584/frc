/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdFollowPath.h"
#include "Robot.h"
#include <pathfinder.h>
#include <iostream>
#include <fstream>

CmdFollowPath::CmdFollowPath() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::subDriveBase.get());
}

// Called just before this Command runs the first time
void CmdFollowPath::Initialize() {
  frc::Timer timer;
  timer.Start();
  const int POINT_LENGTH = 2;
  Waypoint points[POINT_LENGTH];
  Waypoint p1 = {0, 0, d2r(0)};
  Waypoint p2 = {1, 1, d2r(0)};
  points[0] = p1;
  points [1] = p2;

  TrajectoryCandidate candidate;
  // Prepare the Trajectory for Generation.
  //
  // Arguments: 
  // Fit Function:        FIT_HERMITE_CUBIC or FIT_HERMITE_QUINTIC
  // Sample Count:        PATHFINDER_SAMPLES_HIGH (100 000)
  //                      PATHFINDER_SAMPLES_LOW  (10 000)
  //                      PATHFINDER_SAMPLES_FAST (1 000)
  // Time Step:           0.001 Seconds
  // Max Velocity:        15 m/s
  // Max Acceleration:    10 m/s/s
  // Max Jerk:            60 m/s/s/s
  // Change the sample count and/or the time step to generate the trajectory faster
  pathfinder_prepare(points, POINT_LENGTH, FIT_HERMITE_CUBIC, PATHFINDER_SAMPLES_FAST, 0.01, max_velocity, 2.0, 30.0, &candidate);
  length = candidate.length;

  // Array of Segments (the trajectory points) to store the trajectory in

  // *trajectory = (Segment*)malloc(length * sizeof(Segment));
  seg = new Segment[length];
  SmartDashboard::PutNumber("Before generation time", timer.Get());
  // Generate the trajectory
  int result = pathfinder_generate(&candidate, seg);

  SmartDashboard::PutNumber("Time taken to generate path", timer.Get());
  leftTrajectory = new Segment[length];
  rightTrajectory = new Segment[length];

  // The distance between the left and right sides of the wheelbase is 0.6m
  double wheelbase_width = 0.6;

  // Generate the Left and Right trajectories of the wheelbase using the 
  // originally generated trajectory
  pathfinder_modify_tank(seg, length, leftTrajectory, rightTrajectory, wheelbase_width);
  std::ofstream file("/home/lvuser/output.txt");
  file << "x, y, velcoity" << std::endl;
  int i;
  for (i = 0; i < length; i++) {
    Segment s = seg[i];
    file << s.x << ", "<< s.y << ", " << s.velocity << std::endl;
    // printf("Time Step: %f\n", s.dt);
    // printf("Coords: (%f, %f)\n", s.x, s.y);
    // printf("Position (Distance): %f\n", s.position);
    // printf("Velocity: %f\n", s.velocity);
    // printf("Acceleration: %f\n", s.acceleration);
    // printf("Jerk (Acceleration per Second): %f\n", s.jerk);
    // printf("Heading (radians): %f\n", s.heading);
  }
  file.close();
  rightFollower = (EncoderFollower*)malloc(sizeof(EncoderFollower));
  rightFollower->last_error = 0; rightFollower->segment = 0; rightFollower->finished = 0;     // Just in case!

  leftFollower = (EncoderFollower*)malloc(sizeof(EncoderFollower));
  leftFollower->last_error = 0; leftFollower->segment = 0; leftFollower->finished = 0;     // Just in case!
  
  double wheel_circumference = 0.1016 * 3.14158;
  int leftEncoderPosition = 0;
  leftConfig = {leftEncoderPosition, 4096, wheel_circumference,      // Position, Ticks per Rev, Wheel Circumference
               1.0, 0.0, 0.0, 0.01 / max_velocity, 0.0};              // Kp, Ki, Kd and Kv, Ka
  
  int rightEncoderPosition = 0;
  rightConfig = {rightEncoderPosition, 4096, wheel_circumference,
                0.2, 0.0, 0.0, 0.01/ max_velocity, 0.0};
  timer.Stop();
  SmartDashboard::PutBoolean("Ended", false);
  SmartDashboard::PutNumber("Time taken to run everything", timer.Get());
  Robot::subDriveBase->resetYaw();
  Robot::subDriveBase->zeroEncoders();
}

// Called repeatedly when this Command is scheduled to run
void CmdFollowPath::Execute() {
  // // Arg 1: The EncoderConfig
  // // Arg 2: The EncoderFollower for this side
  // // Arg 3: The Trajectory generated from `pathfinder_modify_tank`
  // // Arg 4: The Length of the Trajectory (length used in Segment seg[length];)
  // // Arg 5: The current value of your encoder
  SmartDashboard::PutBoolean("start of exe", true);
  double leftEncoderValue = Robot::subDriveBase->getRawLeftEncoder(); 
  double rightEncoderValue = Robot::subDriveBase->getRawRightEncoder(); 
  double l = pathfinder_follow_encoder(leftConfig, leftFollower, leftTrajectory, length, leftEncoderValue);
  double r = pathfinder_follow_encoder(rightConfig, rightFollower, rightTrajectory, length, rightEncoderValue);

  double gyro_heading = Robot::subDriveBase->getYaw();
  double desired_heading = r2d(leftFollower->heading);

  double angle_difference = desired_heading - gyro_heading;

  double turn = 0.8 * (-1.0/80.0) * angle_difference;

  double leftPower = l + turn;
  double rightPower = r - turn;
  SmartDashboard::PutNumber("Left Power", leftPower);
  //Robot::subDriveBase->tankDrive(leftPower, rightPower);
}

// Make this return true when this Command no longer needs to run execute()
bool CmdFollowPath::IsFinished() { 
  return false; 
}

// Called once after isFinished returns true
void CmdFollowPath::End() {
  SmartDashboard::PutBoolean("Ended", true);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdFollowPath::Interrupted() {}
