#include "subsystems/SubDrivebase.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <wpi/sendable/Sendable.h>

#include "utilities/Vision.h"

SubDrivebase::SubDrivebase() {
  _frontLeft.SetConversionFactor(DIST_CONVERSION);
  _frontRight.SetConversionFactor(DIST_CONVERSION);
  _backLeft.SetConversionFactor(DIST_CONVERSION);
  _backRight.SetConversionFactor(DIST_CONVERSION);

  _backLeft.Follow(_frontLeft);
  _backRight.Follow(_frontRight);

  _field.GetObject("goal")->SetPose({FakeVision::goalPosition, 0_deg});
  frc::SmartDashboard::PutData("field", &_field);
  frc::SmartDashboard::PutData("drivebase/rot controller", &_rotController);
  frc::SmartDashboard::PutData("drivebase/fr", (wpi::Sendable*)&_frontRight);
  frc::SmartDashboard::PutData("drivebase/br", (wpi::Sendable*)&_backRight);
  frc::SmartDashboard::PutData("drivebase/fl", (wpi::Sendable*)&_frontLeft);
  frc::SmartDashboard::PutData("drivebase/bl", (wpi::Sendable*)&_backLeft);
};

void SubDrivebase::Periodic() {
  frc::SmartDashboard::PutNumber("vision/Angle to targ", FakeVision::GetAngleToTarget().value());
  frc::SmartDashboard::PutNumber("vision/Dist to targ", FakeVision::GetDistToTarget().value());
  UpdateOdometry();
  _field.SetRobotPose(_odometry.GetPose());
}

void SubDrivebase::Drive(double speed, double turn) {
  _diffDrive.ArcadeDrive(speed, turn);
}

void SubDrivebase::DriveSpeeds(units::meters_per_second_t left, units::meters_per_second_t right) {
  // Calc how many volts to pump into the motors to make them spin the wheels at those speeds.
  auto leftVolts = _feedforward.Calculate(left);
  auto rightVolts = _feedforward.Calculate(right);

  // Send those voltages to the motors. (note the back motors follow the front ones).
  _frontLeft.SetVoltage(leftVolts);
  _frontRight.SetVoltage(rightVolts);

  // The diff drive gets annoyed if you dont use it frequently. 
  // Feed it to sate its deranged hunger for attention.
  _diffDrive.Feed();
}

void SubDrivebase::DriveTowardPathState(pathplanner::PathPlannerTrajectory::PathPlannerState pathState) {
  // Calc how fast the drive base should be moving in X, Y and rotation. 
  // Y speed will always be zero for a differential tank drive (aka unicycle)
  // This is stored in a ChassisSpeeds object.
  auto chassisSpeeds = _driveController.Calculate(_odometry.GetPose(), pathState.asWPILibState());

  // Calc how fast each wheel should be moving to get the drive base to travel at those speeds.
  auto wheelSpeeds = _kinematics.ToWheelSpeeds(chassisSpeeds);

  // Drive the wheels at calculated speeds
  DriveSpeeds(wheelSpeeds.left, wheelSpeeds.right);
}

void SubDrivebase::RotateTowardZero(units::degree_t angle) {
  double turnRate = _rotController.Calculate(0, angle.value());
  Drive(0, turnRate);
}

void SubDrivebase::UpdateOdometry() {
  _odometry.Update(_navx.GetRotation2d(), _frontLeft.GetPosition(), _frontRight.GetPosition());
}

frc::Pose2d SubDrivebase::GetPose() {
  return _odometry.GetPose();
}

void SubDrivebase::SetPose(frc::Pose2d pose) {
  _odometry.ResetPosition(_navx.GetRotation2d(), _frontLeft.GetPosition(),
                          _frontRight.GetPosition(), pose);
}

void SubDrivebase::DisplayPose(std::string name, frc::Pose2d pose) {
  _field.GetObject(name)->SetPose(pose);
}

void SubDrivebase::DisplayTrajectory(std::string name, frc::Trajectory trajectory) {
  _field.GetObject(name)->SetTrajectory(trajectory);
}

void SubDrivebase::SimulationPeriodic() {
  _diffDriveSim.SetInputs(_frontLeft.GetSimVoltage(), _frontRight.GetSimVoltage());
  _diffDriveSim.Update(20_ms);

  auto leftDist = _diffDriveSim.GetLeftPosition();
  auto rightDist = _diffDriveSim.GetRightPosition();
  auto leftVel = _diffDriveSim.GetLeftVelocity();
  auto rightVel = _diffDriveSim.GetRightVelocity();

  _frontLeft.UpdateSimEncoder(leftDist, leftVel);
  _backLeft.UpdateSimEncoder(leftDist, leftVel);
  _frontRight.UpdateSimEncoder(rightDist, rightVel);
  _backRight.UpdateSimEncoder(rightDist, rightVel);

  _navx.SetAngleAdjustment(-_diffDriveSim.GetHeading().Degrees().value());
}