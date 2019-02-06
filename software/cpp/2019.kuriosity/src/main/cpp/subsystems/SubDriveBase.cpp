/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SubDriveBase.h"
#include "Robot.h"
#include "commands/CmdJoystickDrive.h"
#include "pathfinder.h"
#include <fstream>

SubDriveBase::SubDriveBase() : Subsystem("ExampleSubsystem") {
  //motors
  _srxFrontLeft = Robot::_robotMap->srxDriveBaseFrontLeft;
  _srxBackLeft = Robot::_robotMap->srxDriveBaseBackLeft;
  _srxFrontRight = Robot::_robotMap->srxDriveBaseFrontRight;
  _srxBackRight = Robot::_robotMap->srxDriveBaseBackRight;
  difDrive.reset(new frc::DifferentialDrive(*_srxFrontLeft, *_srxFrontRight));

  //sensors
  _ahrsNavXGyro = Robot::_robotMap->ahrsNavXDriveBase;
  _clsMid = Robot::_robotMap->clsDriveBaseMid;
  _clsFront = Robot::_robotMap->clsDriveBaseFront;
  _ulsGimble = Robot::_robotMap->ulsDriveBaseGimble;
  _ulsBottom = Robot::_robotMap->ulsDriveBaseBottom;
  _clsLineLeft = Robot::_robotMap->clsLineDriveBaseLeft;
  _clsLineRight = Robot::_robotMap->clsLineDriveBaseRight;

  //encoders
  _srxFrontRight->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 10);
  _srxFrontLeft->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 10);
  _srxFrontRight->SetSensorPhase(true);

  rightVelocitySource = new RightVelocitySource();
  leftVelocitySource = new LeftVelocitySource();
  leftVelocityController.reset(new PIDController(0.3, 0.0, 0.0, leftVelocitySource, _srxFrontLeft.get()));
  rightVelocityController.reset(new PIDController(0.3, 0.0, 0.0, rightVelocitySource, _srxFrontRight.get()));

  //not in use
  // _srxBackRight->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 10);
  // _srxBackLeft->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 10);

  _ulsGimble->SetAutomaticMode(true);
  _ulsBottom->SetAutomaticMode(true);

  // Robot constants
  metersPerRotation = 3.14159265359 * WHEEL_DIAMETER;
}
void SubDriveBase::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  SetDefaultCommand(new CmdJoystickDrive());
}

void SubDriveBase::drive(double speed, double rotation) {
  difDrive->ArcadeDrive(-speed, rotation);
}

void SubDriveBase::setTalControlMode(ControlMode controlMode) {
  _srxFrontRight->Set(controlMode, 0);
  _srxFrontLeft->Set(controlMode, 0);
}
void SubDriveBase::tankDriveVelocity(double leftVelocity, double rightVelocity) {
  _srxFrontLeft->Set(ControlMode::Velocity, leftVelocity);
  _srxFrontRight->Set(ControlMode::Velocity, rightVelocity);
  
}

double SubDriveBase::getRawLeftEncoder() {
  SmartDashboard::PutNumber("Left Encoder", _srxFrontLeft->GetSelectedSensorPosition());
  return _srxFrontLeft->GetSelectedSensorPosition(0);
}

double SubDriveBase::getRawRightEncoder() {
  SmartDashboard::PutNumber("Right Encoder", _srxFrontRight->GetSelectedSensorPosition());
  return _srxFrontRight->GetSelectedSensorPosition(0);
}
void SubDriveBase::disablePID() {
  _srxFrontLeft->SetNeutralMode(NeutralMode::Brake);
  _srxFrontRight->SetNeutralMode(NeutralMode::Brake);
  _srxFrontRight->SetInverted(false);
}
//returns velocity in m/s
double SubDriveBase::getRightVelocity() {
  double velocity = _srxFrontRight->GetSelectedSensorVelocity(0);
  velocity = velocity * scaleFactor * 10;
  return velocity;
}

double SubDriveBase::getLeftVelocity() {
  double velocity = _srxFrontLeft->GetSelectedSensorVelocity(0);
  velocity = velocity * scaleFactor * 10;
  return velocity;
}

void SubDriveBase::velocityPIDConfig() {
  difDrive->SetSafetyEnabled(false);
  //left talon
  double kF = 1023/ (3.6/ 0.000078 / 10) + 0.18;
  _srxFrontLeft->ConfigNominalOutputForward(0, kTimeoutMs);
  _srxFrontLeft->ConfigNominalOutputReverse(0, kTimeoutMs);
  _srxFrontLeft->ConfigPeakOutputForward(1, kTimeoutMs);
  _srxFrontLeft->ConfigPeakOutputReverse(-1, kTimeoutMs);

  _srxFrontLeft->Config_kF(kPIDLoopIdx, kF, kTimeoutMs);
  _srxFrontLeft->Config_kP(kPIDLoopIdx, 0.025, kTimeoutMs); //0.046
  _srxFrontLeft->Config_kI(kPIDLoopIdx, 0.0, kTimeoutMs);
  _srxFrontLeft->Config_kD(kPIDLoopIdx, 0, kTimeoutMs);

  //right srx
  _srxFrontRight->ConfigNominalOutputForward(0, kTimeoutMs);
  _srxFrontRight->ConfigNominalOutputReverse(0, kTimeoutMs);
  _srxFrontRight->ConfigPeakOutputForward(1, kTimeoutMs);
  _srxFrontRight->ConfigPeakOutputReverse(-1, kTimeoutMs);

  _srxFrontRight->Config_kF(kPIDLoopIdx, kF, kTimeoutMs);
  _srxFrontRight->Config_kP(kPIDLoopIdx, 0.025, kTimeoutMs); //0.035
  _srxFrontRight->Config_kI(kPIDLoopIdx, 0.0, kTimeoutMs);
  _srxFrontRight->Config_kD(kPIDLoopIdx, 0.0, kTimeoutMs);
  _srxFrontRight->SetNeutralMode(NeutralMode::Coast);
  _srxFrontLeft->SetNeutralMode(NeutralMode::Coast);
}

void SubDriveBase::zeroEncoders() {
  _srxFrontLeft->SetSelectedSensorPosition(0, 0);
  _srxFrontRight->SetSelectedSensorPosition(0, 0);
}

double SubDriveBase::getDistanceTravelled() {
  double encoderTics = (getRawLeftEncoder() + getRawRightEncoder()) / 2;
  double wheelRotations = encoderTics / ENCODER_TICS_PER_ROTATION;
  double distance = wheelRotations * metersPerRotation;
  return distance;  
}

void SubDriveBase::resetYaw(){
  _ahrsNavXGyro->ZeroYaw();
}

double SubDriveBase::getYaw() {
  return _ahrsNavXGyro->GetYaw();
}

bool SubDriveBase::frontHasReachedLine() {
  SmartDashboard::PutNumber("frontHasReachedLine", not(_clsFront->Get()));
  return not(_clsFront->Get());
}

bool SubDriveBase::midHasReachedLine() {
  SmartDashboard::PutNumber("midHasReachedLine", not(_clsMid->Get()));
  return not(_clsMid->Get());
}

void SubDriveBase::brakeRobot() {
    difDrive->ArcadeDrive(-0.4, 0.2);
}

double SubDriveBase::getDistanceToObstical() {
  SmartDashboard::PutNumber("Bottom Ultrasonic Range", _ulsBottom->GetRangeMM());
  SmartDashboard::PutBoolean("Bottom Ultrasonic range valid?", _ulsBottom->IsRangeValid());
  return _ulsBottom->GetRangeMM();
}

//uses the ultrasonic sensor to check whether the cargo ship bay has a hatch panel on it
bool SubDriveBase::isBayEmpty() {
  if (_ulsGimble->GetRangeMM() < 500) {
    return false;
  }
  else {
    return true;
  }
}
void SubDriveBase::pidPositionConfig() {
  _srxFrontLeft->ConfigNominalOutputForward(0, kTimeoutMs);
  _srxFrontLeft->ConfigNominalOutputReverse(0, kTimeoutMs);
  _srxFrontLeft->ConfigPeakOutputForward(0.8, kTimeoutMs);
  _srxFrontLeft->ConfigPeakOutputReverse(-0.8, kTimeoutMs);

  _srxFrontLeft->Config_kF(kPIDLoopIdx, 0, kTimeoutMs);
  _srxFrontLeft->Config_kP(kPIDLoopIdx, 0.3, kTimeoutMs); //0.046
  _srxFrontLeft->Config_kI(kPIDLoopIdx, 0.0, kTimeoutMs);
  _srxFrontLeft->Config_kD(kPIDLoopIdx, 0, kTimeoutMs);

  //right srx
  _srxFrontRight->ConfigNominalOutputForward(0, kTimeoutMs);
  _srxFrontRight->ConfigNominalOutputReverse(0, kTimeoutMs);
  _srxFrontRight->ConfigPeakOutputForward(0.8, kTimeoutMs);
  _srxFrontRight->ConfigPeakOutputReverse(-0.8, kTimeoutMs);

  _srxFrontRight->Config_kF(kPIDLoopIdx, 0, kTimeoutMs);
  _srxFrontRight->Config_kP(kPIDLoopIdx, 0.3, kTimeoutMs); //0.035
  _srxFrontRight->Config_kI(kPIDLoopIdx, 0.0, kTimeoutMs);
  _srxFrontRight->Config_kD(kPIDLoopIdx, 0.0, kTimeoutMs);
  _srxFrontRight->SetNeutralMode(NeutralMode::Brake);
  _srxFrontLeft->SetNeutralMode(NeutralMode::Brake);
}
double SubDriveBase::positionPID(double distance) {
  _srxFrontRight->Set(ControlMode::Position, -distance);
  _srxFrontLeft->Set(ControlMode::Position, distance);
}

bool SubDriveBase::isLeftClsOnLine() {
  return not(_clsLineLeft->Get());
}

bool SubDriveBase::isRightClsOnLine() {
  return not(_clsLineRight->Get());
}

Segment* SubDriveBase::generatePath(){
  frc::Timer timer;
  timer.Start();
  const int POINT_LENGTH = 2;
  Waypoint points[POINT_LENGTH];
  Waypoint p1 = {0, 0, d2r(90)};
  Waypoint p2 = {0.2, 3, d2r(90)};
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
  double max_velocity = 4.2;
  double time_step = 0.01;
  double max_accel = 10.0;
  double max_jerk= 60.0;
  pathfinder_prepare(points, POINT_LENGTH, FIT_HERMITE_CUBIC, PATHFINDER_SAMPLES_FAST, time_step, max_velocity, max_accel, max_jerk, &candidate);
  pathLength = candidate.length;

  // Array of Segments (the trajectory points) to store the trajectory in
  Segment * seg = new Segment[pathLength];
  SmartDashboard::PutNumber("Before generation time", timer.Get());
  // Generate the trajectory
  int result = pathfinder_generate(&candidate, seg);
  std::ofstream file("/home/lvuser/output.txt");
  file << "x, y, velcoity" << std::endl;
  int i;
  for (i = 0; i < pathLength; i++) {
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
  SmartDashboard::PutNumber("Time taken to generate path", timer.Get());
  timer.Stop();
  return seg;
}

int SubDriveBase::getPathLength() {
  return pathLength;
}
