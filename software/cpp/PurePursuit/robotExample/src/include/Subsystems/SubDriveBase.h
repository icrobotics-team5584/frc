#pragma once

#include <AHRS.h>
#include <WPILib.h>
#include <ctre/Phoenix.h>
#include "Commands/Subsystem.h"

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

    shared_ptr<AHRS> ahrsNavX;

   public:
    SubDriveBase();
    void InitDefaultCommand() override;
    void drive(double speed, double rotation, bool squaredInput = false);
    double getAngle();
    double getDistance();
};
