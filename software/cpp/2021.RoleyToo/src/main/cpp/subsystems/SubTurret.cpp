// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubTurret.h"

SubTurret::SubTurret() {
  _networktables = nt::NetworkTableInstance::GetDefault();
  _limelight = _networktables.GetTable("limelight");
  LimeLEDOff();

  _spmFlywheelRight.RestoreFactoryDefaults();
  _spmFlywheelLeft.RestoreFactoryDefaults();
  _spmTurret.RestoreFactoryDefaults();
  _spmHood.RestoreFactoryDefaults();

  _spmFlywheelRight.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
  _spmFlywheelLeft.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
  _spmTurret.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
  _spmHood.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

  _spmFlywheelLeft.Follow(_spmFlywheelRight, true);

  _spmFlywheelRight.SetSmartCurrentLimit(50);
  _spmFlywheelLeft.SetSmartCurrentLimit(50);
  _spmTurret.SetSmartCurrentLimit(20);
  _spmHood.SetSmartCurrentLimit(20);

  _spmHood.SetInverted(true);

  _encHood.SetPosition(0);

  frc::SmartDashboard::PutNumber("Turret Speed", 0);
}

// This method will be called once per scheduler run
void SubTurret::Periodic() {
  _targetX = _limelight->GetNumber("tx", 0.0);
  _targetY = _limelight->GetNumber("ty", 0.0);
  _targetA = _limelight->GetNumber("ta", 0.0);
  _targetVisible = _limelight->GetNumber("tv", 0.0);
  frc::SmartDashboard::PutNumber("Flywheel RPM", GetFlywheelRPM());
  frc::SmartDashboard::PutNumber("Flywheel Current", _spmFlywheelRight.GetOutputCurrent());

  frc::SmartDashboard::PutNumber("Target Angle", GetY());

  frc::SmartDashboard::PutNumber("Turret Angle", GetTurretAngle());
  frc::SmartDashboard::PutNumber("Hood Angle", GetHoodPos());

  frc::SmartDashboard::PutBoolean("Hood Limit", GetHoodLimit());

  //std::cout << _spmTurret.Get() << "   " << _spmTurret.GetOutputCurrent() << "\n";
}

double SubTurret::GetX() {
  return _targetX;
}

double SubTurret::GetY() {
  return _targetY;
}

double SubTurret::GetTargetArea() {
  return _targetA;
}

bool SubTurret::CheckTarget() {
  return _targetVisible;
}

bool SubTurret::GetLeftLimit() {
    return _hlfTurretLeft.Get();
}

bool SubTurret::GetRightLimit() {
    return !_hlfTurretRight.Get();  // Returns true when turret hits limit
}

double SubTurret::GetTurretAngle() {
  return (_encTurret.GetPosition());
}

void SubTurret::ResetTurretEncoder() {
  _encTurret.SetPosition(0);
}

void SubTurret::SetTurret(double speed) {
  _spmTurret.Set(speed);
}

void SubTurret::LimeLEDOn() {
  _limelight->PutNumber("ledMode", 3);
}

void SubTurret::LimeLEDOff() {
  _limelight->PutNumber("ledMode", 1);
}

void SubTurret::SetFlywheel(double speed) {
  _spmFlywheelRight.Set(speed);
}

double SubTurret::GetFlywheelRPM() {
  return _encFlywheel.GetVelocity();
}

void SubTurret::SetHood(double speed) {
  _spmHood.Set(speed);
}

double SubTurret::GetHoodPos() {
  return (_encHood.GetPosition() + _hoodInitialAngle);
}

void SubTurret::ResetHoodEncoder() {
  _encHood.SetPosition(0);
}

bool SubTurret::GetHoodLimit() {
  return _hlfHoodDown.Get();
}

double SubTurret::EstimateDistance() {
  if (!_targetVisible) {
    return 0;
  }
  return ((_targetHeight - _limelightHeight) / (tan(_limelightAngle - GetY())));
}

void SubTurret::SetReady(bool ready) {
  ReadyToShoot = ready;
}

bool SubTurret::IsReady() {
  return ReadyToShoot;
}

double SubTurret::CalculateHoodAngle(double x) {
  return (-0.000008*pow(x,4)) + (0.004*pow(x,3)) - (0.0666*pow(x,2)) + (0.3915*x) + (9.5094);
}

std::pair<double, double> SubTurret::GetCrosshair() {
  std::vector<double> x = _limelight->GetEntry("tcornx").GetDoubleArray(std::vector<double>());
  std::vector<double> y = _limelight->GetEntry("tcorny").GetDoubleArray(std::vector<double>());

  // Initialise 4x4 matrix
  double dist[4][4] =
  {
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0}
  };

  // Calculate distance between all nodes and store in matrix
  for (int i=0; i<4; i++)
  {
    for (int j=i+1; j<4; j++)
    {
      double x1 = x[i];
      double x2 = x[j];
      double y1 = y[i];
      double y2 = y[j];
      dist[i][j] = std::sqrt(pow(x2-x1,2)+pow(y2-y1,2));
    }
  }

  // Associate distances to node pairs
  double distSort[6][3] =
  {
    {0,0,0},
    {0,0,0},
    {0,0,0},
    {0,0,0},
    {0,0,0},
    {0,0,0}
  };

  int k = 0;
  for (int i=0; i<4; i++)
  {
    for (int j=i+1; j<4; j++)
    {
      distSort[k][0] = i;
      distSort[k][0] = j;
      distSort[k][0] = dist[i][j];
      k++;
    }
  }

  // Get the third and fourth longest lines (the long sides on the rectangle)
  double longSides[2][3] =
  {
    {0,0,0},
    {0,0,0}
  };

  for (int i=0; i<4; i++)
  {
    double maxItem[4];
    for (int j=0; j<6; j++)
    {
      if (distSort[j][2] > maxItem[2])
      {
        maxItem[0] = distSort[j][0];
        maxItem[1] = distSort[j][1];
        maxItem[2] = distSort[j][2];
        maxItem[3] = i;
      }
    }
    distSort[(int)maxItem[3]][0] = 0;
    distSort[(int)maxItem[3]][1] = 0;
    distSort[(int)maxItem[3]][2] = 0;
    if (i > 1)      // Exclude the first 2 values (diagonal lines)
    {
      longSides[i-2][0] = maxItem[0];
      longSides[i-2][1] = maxItem[1];
      longSides[i-2][2] = maxItem[2];
    }
  }

  // Find the midpoints of each long side
  std::array<std::pair<double, double>, 2> midpoints;
  for (int i=0; i<2; i++)
  {
    double x1 = x[longSides[i][0]];
    double y1 = y[longSides[i][0]];
    double x2 = x[longSides[i][1]];
    double y2 = y[longSides[i][1]];

    midpoints[i].first = (x1+x2)/2;
    midpoints[i].second = (y1+y2)/2;
  }

  // Return the coordinate of the lower midpoint
  std::pair<double, double> target;
  target = midpoints[0].second < midpoints[1].second ? midpoints[0] : midpoints[1];
  return target;
}