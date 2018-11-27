#pragma once

#include "Commands/Subsystem.h"
#include <ctre/Phoenix.h>
#include <WPILib.h>

using namespace std;

class SubDriveBase : public frc::Subsystem {
private:
  shared_ptr<WPI_TalonSRX> srxLeft;
  shared_ptr<WPI_TalonSRX> srxRight;
  shared_ptr<WPI_TalonSRX> srxLeftSlave;
  shared_ptr<WPI_TalonSRX> srxRightSlave;
  unique_ptr<frc::DifferentialDrive> diffDrive;

  unique_ptr<SpeedControllerGroup> scgLeft;
  unique_ptr<SpeedControllerGroup> scgRight;

public:
  SubDriveBase();
  void InitDefaultCommand() override;
  void drive(double speed, double rotation, bool squaredInput = false);
};
