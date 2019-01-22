#include "purePursuit/include/DvoTank.h"
#include "Robot.h"

void DvoTank::set(double curve) {
    Robot::subDriveBase->drive(0, curve);
}