#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/smartdashboard/Field2d.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/kinematics/DifferentialDriveOdometry.h>
#include <frc/kinematics/DifferentialDriveKinematics.h>
#include <frc/simulation/DifferentialDrivetrainSim.h>
#include <frc/system/plant/DCMotor.h>
#include <frc/controller/SimpleMotorFeedforward.h>
#include <frc/controller/PIDController.h>
#include <frc/controller/LTVUnicycleController.h>
#include <frc/controller/RamseteController.h>
#include <units/moment_of_inertia.h>
#include <units/angle.h>
#include <units/length.h>
#include <units/mass.h>
#include <AHRS.h>
#include <pathplanner/lib/PathPlannerTrajectory.h>
#include <pathplanner/lib/commands/FollowPathWithEvents.h>

#include "Constants.h"
#include "utilities/ICSparkMax.h"

class SubDrivebase : public frc2::SubsystemBase {
 public:
  SubDrivebase();
  static SubDrivebase& GetInstance() {
    static SubDrivebase inst;
    return inst;
  }

  void Periodic() override;
  void SimulationPeriodic() override;
  void UpdateOdometry();
  void Drive(double speed, double turn);
  void DriveSpeeds(units::meters_per_second_t left, units::meters_per_second_t right);
  void DriveTowardPathState(pathplanner::PathPlannerTrajectory::PathPlannerState pathState);
  void DriveVoltsFromDB();
  void RotateTowardZero(units::degree_t angle);
  frc::Pose2d GetPose();
  void SetPose(frc::Pose2d pose);
  void DisplayPose(std::string name, frc::Pose2d pose);
  void DisplayTrajectory(std::string name, frc::Trajectory trajectory);
  frc::DifferentialDriveKinematics GetKinematics() { return _kinematics; }
  frc::RamseteController GetController() { return _driveController; }

 private:
  // Data
  static constexpr double GEARING = 8.0;
  static constexpr units::kilogram_square_meter_t MOI = 1_kg_sq_m;
  static constexpr units::kilogram_t MASS = 10_kg;
  static constexpr units::meter_t WHEEL_RADIUS = 2_in;
  static constexpr units::meter_t TRACK_WIDTH = 0.8_m;
  static constexpr double DIST_CONVERSION = WHEEL_RADIUS.value() / GEARING;
  static constexpr double ROT_P = 0.05;
  static constexpr double ROT_I = 0.0;
  static constexpr double ROT_D = 0.001;
  static constexpr units::unit_t<frc::RamseteController::b_unit> RAMSETE_B{4};
  static constexpr units::unit_t<frc::RamseteController::zeta_unit> RAMSETE_ZETA{0.4};

  // Electronics
  // give the ICSparkMaxes the meters units so we can give it targets in meters and get encoder 
  // readings in meters and meters per second. 
  // This would have been rotations and rotations per min by default
  ICSparkMax<units::meter> _frontLeft{canid::frontLeftDrive};
  ICSparkMax<units::meter> _backLeft{canid::backLeftDrive};
  ICSparkMax<units::meter> _frontRight{canid::frontRightDrive};
  ICSparkMax<units::meter> _backRight{canid::backRightDrive};
  AHRS _navx{frc::SerialPort::kMXP};

  // Controllers and kinematics
  frc::SimpleMotorFeedforward<units::meters> _feedforward{0.0_V, 3.2_V / 1_mps, 0.2_V / 1_mps_sq};
  frc::PIDController _rotController{ROT_P, ROT_I, ROT_D};
  frc::DifferentialDriveOdometry _odometry{0_deg, 0_m, 0_m};
  frc::DifferentialDrive _diffDrive{_frontLeft, _frontRight};
  frc::RamseteController _driveController{RAMSETE_B, RAMSETE_ZETA};
  frc::DifferentialDriveKinematics _kinematics{TRACK_WIDTH};

  // Simulation
  frc::Field2d _field;
  frc::sim::DifferentialDrivetrainSim _diffDriveSim{frc::DCMotor::NEO(2), GEARING,    MOI, MASS,
                                                    WHEEL_RADIUS,         TRACK_WIDTH};
};
