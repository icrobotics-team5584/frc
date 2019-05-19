#include "purePursuit/include/DvoTank.h"
#include "Robot.h"

void DvoTank::set(DriveOutput::MotorVelocities motorVelocities) {
    Robot::subDriveBase->tankDriveVelocity(motorVelocities.first, motorVelocities.second);
}